export module Zephyr.Renderer.Types.Frustum;

export import Zephyr.Renderer.Types.Vertex3d;
import std;

export namespace Zephyr
{
	struct Plane
	{
		glm::vec3 Normal{};
		float Distance{};

		constexpr float SignedDistance(glm::vec3 point) const noexcept
		{
			return glm::dot(Normal, point) + Distance;
		}

		static Plane Create(glm::vec4 p)
		{
			Plane out{ glm::vec3(p), p.w };
			const float len = glm::length(out.Normal);

			if (len > 0.0f)
			{
				const float inv = 1.0f / len;
				out.Normal *= inv;
				out.Distance *= inv;
			}

			return out;
		}
	};

	struct AABB
	{
		glm::vec3 Min{};
		glm::vec3 Max{};

		constexpr glm::vec3 GetCenter() const noexcept { return (Min + Max) * 0.5f; }
		constexpr glm::vec3 GetExtent() const noexcept { return (Max - Min) * 0.5f; }

		static constexpr Zephyr::AABB ComputeLocalBounds(std::span<const Vertex3D> vertices);
		static AABB TransformAabbToWorld(const Zephyr::AABB& localAabb, const glm::mat4& localToWorld);
	};

	class Frustum
	{
	public:
		static Frustum ExtractFromMatrix(const glm::mat4& viewProjection);

		bool IsVisible(AABB bounds) const;
		bool IsVisible(glm::vec3 point) const;

	private:
		std::array<Plane, 6> m_Planes;
	};

	Frustum Frustum::ExtractFromMatrix(const glm::mat4& viewProjection)
	{
		Frustum fr{};

		const glm::vec4 r0 = glm::row(viewProjection, 0);
		const glm::vec4 r1 = glm::row(viewProjection, 1);
		const glm::vec4 r2 = glm::row(viewProjection, 2);
		const glm::vec4 r3 = glm::row(viewProjection, 3);

		fr.m_Planes[0] = Plane::Create(r3 + r0); // Left   :  w + x >= 0
		fr.m_Planes[1] = Plane::Create(r3 - r0); // Right  :  w - x >= 0
		fr.m_Planes[2] = Plane::Create(r3 + r1); // Bottom :  w + y >= 0
		fr.m_Planes[3] = Plane::Create(r3 - r1); // Top    :  w - y >= 0

		fr.m_Planes[4] = Plane::Create(r2);      // Near   :  z >= 0
		fr.m_Planes[5] = Plane::Create(r3 - r2); // Far    :  w - z >= 0

		return fr;
	}

	bool Frustum::IsVisible(glm::vec3 point) const
	{
		for (const Plane& plane : m_Planes)
		{
			if (plane.SignedDistance(point) < 0.0f)
				return false;
		}

		return true;
	}

	bool Frustum::IsVisible(AABB bounds) const
	{
		const glm::vec3 boxCenter = bounds.GetCenter();
		const glm::vec3 boxExtents = bounds.GetExtent();

		for (const Plane& plane : m_Planes)
		{
			const float centerDistance = plane.SignedDistance(boxCenter);
			const glm::vec3 absNormal = glm::abs(plane.Normal);

			const float projectedRadius =
				boxExtents.x * absNormal.x +
				boxExtents.y * absNormal.y +
				boxExtents.z * absNormal.z;

			if (centerDistance + projectedRadius < 0.0f)
				return false;
		}

		return true;
	}

	constexpr AABB AABB::ComputeLocalBounds(std::span<const Vertex3D> vertices)
	{
		AABB bounds{};
		if (vertices.empty())
			return bounds;

		glm::vec3 minPoint = vertices[0].Position;
		glm::vec3 maxPoint = vertices[0].Position;

		for (size_t i = 1; i < vertices.size(); ++i)
		{
			minPoint = glm::min(minPoint, vertices[i].Position);
			maxPoint = glm::max(maxPoint, vertices[i].Position);
		}

		bounds.Min = minPoint;
		bounds.Max = maxPoint;
		return bounds;
	}

	AABB AABB::TransformAabbToWorld(const Zephyr::AABB& localAabb, const glm::mat4& localToWorld)
	{
		const std::array<glm::vec3, 8> localCorners = 
		{
			glm::vec3{ localAabb.Min.x, localAabb.Min.y, localAabb.Min.z },
			glm::vec3{ localAabb.Max.x, localAabb.Min.y, localAabb.Min.z },
			glm::vec3{ localAabb.Min.x, localAabb.Max.y, localAabb.Min.z },
			glm::vec3{ localAabb.Max.x, localAabb.Max.y, localAabb.Min.z },
			glm::vec3{ localAabb.Min.x, localAabb.Min.y, localAabb.Max.z },
			glm::vec3{ localAabb.Max.x, localAabb.Min.y, localAabb.Max.z },
			glm::vec3{ localAabb.Min.x, localAabb.Max.y, localAabb.Max.z },
			glm::vec3{ localAabb.Max.x, localAabb.Max.y, localAabb.Max.z },
		};

		glm::vec3 worldMin = glm::vec3(localToWorld * glm::vec4(localCorners[0], 1.0f));
		glm::vec3 worldMax = worldMin;

		for (size_t cornerIndex = 1; cornerIndex < localCorners.size(); ++cornerIndex)
		{
			const glm::vec3 worldCorner = glm::vec3(localToWorld * glm::vec4(localCorners[cornerIndex], 1.0f));
			worldMin = glm::min(worldMin, worldCorner);
			worldMax = glm::max(worldMax, worldCorner);
		}

		return Zephyr::AABB{ .Min = worldMin, .Max = worldMax };
	}
}