#include<iostream>
#include<fstream>
#include<string>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include<pcl/visualization/cloud_viewer.h>

#include<liblas/liblas.hpp>
#include<liblas/reader.hpp>
#include<liblas/factory.hpp>
#include<liblas/point.hpp>

using namespace std;

int main(int argc, char** argv)
{
    //las file route and pcd file output route
    const char* lasfile = "/home/yanxie/libLAS/las2pcd/las_demo/S2223526_20200902-040457_0002_LAS1_2.las";
    const char* pcdfile = "/home/yanxie/libLAS/las2pcd/pcd_demo/S2223526_20200902-040457_0002_LAS1_2.pcd";
    
    //open.las file
    std::ifstream ifs;
    ifs.open("/home/yanxie/libLAS/las2pcd/las_demo/S2223526_20200902-040457_0002_LAS1_2.las", std::ios::in | std::ios::binary);
    if (!ifs.is_open())
    {
        std::cout << "cannot open .las" << std::endl;
        return (0);
    }
    
    //liblas read .las file 
    std::cout << "read .las file" << std::endl;
    liblas::ReaderFactory f;
    liblas::Reader reader = f.CreateWithStream(ifs);
    liblas::Header const& header= reader.GetHeader();
    long int count = header.GetPointRecordsCount();
    std::cout << "points count:" << count << '\n'<< std::endl;
    
    //declare pcl point cloud
    pcl::PointCloud<pcl::PointXYZ>::Ptr pointcloudPtr(new pcl::PointCloud<pcl::PointXYZ>);
    //pcl width:
    //disorderly pcl，width=pcl amount，
    //orderly pcl，width=every row pcl amount
    pointcloudPtr->width = count;
    //pcl height:
    //disorderly pcl，height=1，
    //orderly pcl，height=pcl's row number
    pointcloudPtr->height = 1;
    pointcloudPtr->resize(count);
    pointcloudPtr->is_dense = false;

    int i = 0;
    while (reader.ReadNextPoint())
    {
        liblas::Point const& p = reader.GetPoint();
        //this  “->” replace to  “.” will be fail
        pointcloudPtr->points[i].x = p.GetX();
        pointcloudPtr->points[i].y = p.GetY();
        pointcloudPtr->points[i].z = p.GetZ();
        ++i;
    }
    
    //write to.pcd file
    std::cout << "save .pcd" <<std::endl;
    pcl::io::savePCDFileASCII("/home/yanxie/libLAS/las2pcd/pcd_demo/S2223526_20200902-040457_0002_LAS1_2.pcd", *pointcloudPtr);
    std::cout << "saved successful" <<std::endl;
    
    std::cout << "show" <<std::endl;
    pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
    viewer.showCloud(pointcloudPtr);
    while (!viewer.wasStopped())
    {
    }
    return (0);
}
