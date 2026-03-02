#include "RealtimeMesher.h"
#include <iomanip>
#include <iostream>

RealtimeMesher::RealtimeMesher()
{
    trajFile.open("trajectory.txt");
    trajFile << std::fixed << std::setprecision(9);
}

RealtimeMesher::~RealtimeMesher()
{
    std::cout << "=========================\n";
    std::cout << "Voxel size: " << voxelSize << " m\n";
    std::cout << "Total voxels: " << voxelMap.size() << "\n";
    std::cout << "=========================\n";

    std::cout << "Raw points: " << rawPointCount << "\n";
    std::cout << "Filtered voxels: " << voxelMap.size() << "\n";
    std::cout << "Reduction: "
            << 100.0 * (1.0 - double(voxelMap.size()) / rawPointCount)
            << " %\n";


    std::ofstream ply("cloud.ply");

    ply << "ply\nformat ascii 1.0\n";
    ply << "element vertex " << voxelMap.size() << "\n";
    ply << "property float x\nproperty float y\nproperty float z\n";
    ply << "end_header\n";

    for(const auto& kv : voxelMap)
    {
        const auto& p = kv.second;
        ply << p.x() << " " << p.y() << " " << p.z() << "\n";
    }


    ply.close();
}


void RealtimeMesher::integrate(double timestamp,
                               const Eigen::Vector3d& t,
                               const Eigen::Quaterniond& q)
{
    if(!trajFile.is_open()) return;

    trajFile << timestamp << " "
             << t.x() << " "
             << t.y() << " "
             << t.z() << " "
             << q.x() << " "
             << q.y() << " "
             << q.z() << " "
             << q.w() << "\n";
}

void RealtimeMesher::addPoint(const Eigen::Vector3d& p)
{
    if(std::isnan(p.x()) || std::isnan(p.y()) || std::isnan(p.z()))
    {
        std::cout << "NaN detected!" << std::endl;
        return;
    }

    int vx = std::floor(p.x() / voxelSize);
    int vy = std::floor(p.y() / voxelSize);
    int vz = std::floor(p.z() / voxelSize);

    VoxelKey key{vx, vy, vz};

    rawPointCount++;

    static int debugCounter = 0;
    debugCounter++;
    if(debugCounter % 10000 == 0)
        std::cout << "Points processed: " << debugCounter << std::endl;

    if(voxelMap.find(key) == voxelMap.end())
    {
        voxelMap[key] = p;
    }
}

void RealtimeMesher::savePLY(const std::string& filename)
{
    std::ofstream ply(filename);

    ply << "ply\nformat ascii 1.0\n";
    ply << "element vertex " << voxelMap.size() << "\n";
    ply << "property float x\n";
    ply << "property float y\n";
    ply << "property float z\n";
    ply << "end_header\n";

    for(const auto& kv : voxelMap)
    {
        const auto& p = kv.second;
        ply << p.x() << " "
            << p.y() << " "
            << p.z() << "\n";
    }

    ply.close();

    std::cout << "Saved cloud with "
              << voxelMap.size()
              << " voxels.\n";
}