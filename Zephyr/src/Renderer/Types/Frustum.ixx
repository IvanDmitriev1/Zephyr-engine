export module Zephyr.Renderer.Types.Frustum;

export import glm;
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
	};

	struct AABB
	{
		glm::vec3 Min{};
		glm::vec3 Max{};

		constexpr glm::vec3 GetCenter() const noexcept { return (Min + Max) * 0.5f; }
		constexpr glm::vec3 GetExtent() const noexcept { return (Max - Min) * 0.5f; }
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


		return Frustum();
	}

	bool Frustum::IsVisible(AABB bounds) const
	{
		return false;
	}

	bool Frustum::IsVisible(glm::vec3 point) const
	{
		return false;
	}
}