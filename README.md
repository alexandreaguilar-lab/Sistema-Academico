# 🎓 Nexus Academy - Sistema de Gestión Académica

Este es un sistema de gestión académica desarrollado en **C++** que se integra con una base de datos **MariaDB/MySQL**.

## ✨ Características
- **Búsqueda:** Localización por ID.
- **Cuadro de Honor:** Top 5 mejores notas.
- **Alumnos en Riesgo:** Listado de notas < 4.
- **Actualización:** Modificación de notas y celular.

## 📋 Requisitos
1. Servidor MariaDB/MySQL.
2. Librería `libmysqlclient`.

## 🚀 Compilación
```bash
g++ main.cpp -o sistema_academico `mysql_config --cflags --libs`
```
