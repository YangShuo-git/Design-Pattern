#include <iostream>
#include <string>
 
using namespace std;
 
 
// 尼康相机类（适配者）
class NikonCamera
{
public:
    // 打开相机
    void openNikonCamera() {
        cout << "尼康相机：打开相机。" << endl;
    }
    // 关闭相机
    void closeNikonCamera() {
        cout << "尼康相机：关闭相机。" << endl;
    }
    // 打开曝光设置
    void openExposureSettings() {
        cout << "尼康相机：打开曝光设置。" << endl;
    }
};

// 相机接口类
class Camera
{
public:
    // 构造函数
    Camera() {};
    // 析构函数
    virtual ~Camera() {};
    // 打开相机
    virtual void openCamera() = 0;
    // 关闭相机
    virtual void closeCamera() = 0;
    // 配置属性
    virtual void setConfig() = 0;
};
 
// 相机适配器类
class CameraAdapter :public Camera, public NikonCamera
{
public:
    // 打开相机
    virtual void openCamera() {
        openNikonCamera();
    }
    // 关闭相机
    virtual void closeCamera() {
        closeNikonCamera();
    }
    // 配置属性
    virtual void setConfig() {
        // 打开曝光设置
        openExposureSettings();
    }
};

int main()
{
     Camera *m_camera = new CameraAdapter();
     // 打开相机
     m_camera->openCamera();
     // 配置相机
     m_camera->setConfig();
     // 关闭相机
     m_camera->closeCamera();
     delete m_camera;
     return 0;
}