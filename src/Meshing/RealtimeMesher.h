#include <fstream>
#include <vector>
#include <unordered_map>
#include <Eigen/Dense>

struct VoxelKey
{
    int x, y, z;

    bool operator==(const VoxelKey& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

struct VoxelHash
{
    std::size_t operator()(const VoxelKey& k) const
    {
        return std::hash<int>()(k.x * 73856093 ^
                                k.y * 19349663 ^
                                k.z * 83492791);
    }
};

class RealtimeMesher
{
public:
    RealtimeMesher();
    ~RealtimeMesher();

    void integrate(double timestamp,
                   const Eigen::Vector3d& t,
                   const Eigen::Quaterniond& q);

    void addPoint(const Eigen::Vector3d& p);

    void savePLY(const std::string& filename);

private:
    std::ofstream trajFile;
    std::unordered_map<VoxelKey, Eigen::Vector3d, VoxelHash> voxelMap;
    double voxelSize = 0.05; // 5 cm
    size_t rawPointCount = 0;
};
