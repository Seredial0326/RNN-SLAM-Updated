# RNN-SLAM - Actualizado Ubuntu 22.04

Sistema SLAM (Simultaneous Localization and Mapping) que combina Direct Sparse Odometry (DSO) con estimación de profundidad mediante Redes Neuronales Recurrentes (RNN) para reconstrucción 3D densa.

## 🎯 Características

- **DSO (Direct Sparse Odometry)**: Tracking de cámara preciso usando métodos directos
- **RNN para Estimación de Profundidad**: Estimación densa de profundidad usando contexto temporal
- **Reconstrucción 3D**: Generación de mallas 3D densas
- **Visualización en Tiempo Real**: Interface 3D con Pangolin

## 📋 Requisitos

### Hardware
- CPU: 4+ cores (recomendado: 8 cores)
- RAM: 16GB mínimo
- GPU: NVIDIA con CUDA 11.8+ (opcional pero recomendado)
- Disco: 50GB libres

### Software
- Ubuntu 22.04 LTS
- GCC 11+
- CMake 3.20+
- CUDA 11.8 o 12.x (opcional)
- Python 3.10+

### Bibliotecas
- Eigen 3.4+
- OpenCV 4.5+
- Pangolin 0.8
- Boost 1.74+
- TensorFlow 2.11 (CPU o GPU)

## 🚀 Instalación

### 1. Clonar repositorio
```bash
git clone https://github.com/Seredial0326/RNN-SLAM-Updated
cd RNN-SLAM-Updated
```

### 2. Instalar dependencias
```bash
# Ejecutar script de instalación
chmod +x scripts/install_dependencies.sh
./scripts/install_dependencies.sh
```

### 3. Compilar
```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
```

## 📖 Uso

### Procesamiento de Secuencia
```bash
./build/rnn_slam_vm \
    files=/path/to/images \
    calib=/path/to/camera.txt \
    mode=1 \
    preset=0 \
    nogui=0
```

### Parámetros

- `files`: Directorio con imágenes de entrada
- `calib`: Archivo de calibración de cámara
- `mode`: 0=DSO solo, 1=DSO+RNN, 2=RNN solo
- `preset`: 0=default, 1=high quality, 2=fast
- `nogui`: 0=mostrar visualización, 1=headless

## 📚 Documentación

- [Guía de Instalación](docs/INSTALLATION.md)
- [Manual de Usuario](docs/USER_GUIDE.md)
- [Arquitectura del Sistema](docs/ARCHITECTURE.md)
- [Troubleshooting](docs/TROUBLESHOOTING.md)

## 🔄 Cambios desde Versión Original

- ✅ Actualizado a Ubuntu 22.04 LTS
- ✅ Soporte para Pangolin 0.8
- ✅ Compatibilidad con OpenCV 4.x
- ✅ Modernización de dependencias
- ✅ Mejoras en CMakeLists.txt
- ✅ Documentación actualizada

## 📝 Créditos

Basado en el trabajo original de [RicardoEspinosaLoera/RNN-SLAM](https://github.com/RicardoEspinosaLoera/RNN-SLAM)

## 📄 Licencia

GPL-3.0 License - ver archivo [LICENSE](LICENSE)

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Por favor:
1. Fork el proyecto
2. Crea una rama para tu feature (`git checkout -b feature/NuevaCaracteristica`)
3. Commit tus cambios (`git commit -m 'Añadir nueva característica'`)
4. Push a la rama (`git push origin feature/NuevaCaracteristica`)
5. Abre un Pull Request

## 📧 Contacto

Tu Nombre - seredial0326@gmail.com

Project Link: https://github.com/Seredial0326/RNN-SLAM-Updated
