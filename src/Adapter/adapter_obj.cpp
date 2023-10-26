#include <iostream>
#include <string>
using namespace std;
 

// 对象适配器模式 

// 徕卡相机类（适配者类）
class LeicaCamera
{
public:
    // 打开相机
    void openLeicaCamera() {
        cout << "徕卡相机：打开相机。" << endl;
    }
    // 关闭相机
    void closeLeicaCamera() {
        cout << "徕卡相机：关闭相机。" << endl;
    }
    // 打开曝光设置
    void openExposureSettings() {
        cout << "徕卡相机：打开曝光设置。" << endl;
    }
};

// 接口类
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
 
// 相机类（适配器类）
class CameraAdapter :public Camera
{
public:
    // 构造函数
    CameraAdapter() {
        m_leicaCamera = new LeicaCamera();
    }
    // 析构函数
    virtual ~CameraAdapter() {
        if (m_leicaCamera != nullptr) {
            delete m_leicaCamera;
            m_leicaCamera = nullptr;
        }
    }

    // 打开相机
    void openCamera() {
        m_leicaCamera->openLeicaCamera();
    }
    // 关闭相机
    void closeCamera() {
        m_leicaCamera->closeLeicaCamera();
    }
    // 配置属性
    void setConfig() {
        // 打开曝光设置
        m_leicaCamera->openExposureSettings();
    }

private:
    LeicaCamera *m_leicaCamera; // 适配者类实例
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