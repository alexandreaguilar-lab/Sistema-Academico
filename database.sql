-- Crear la base de datos
CREATE DATABASE IF NOT EXISTS nexus_academy;
USE nexus_academy;

-- Crear la tabla de alumnos
CREATE TABLE IF NOT EXISTS alumnos (
    id INT PRIMARY KEY,
    nombre VARCHAR(50) NOT NULL,
    apellido VARCHAR(50) NOT NULL,
    celular VARCHAR(20),
    nota_final DECIMAL(4,2) NOT NULL
);

-- Insertar 15 alumnos de prueba
SELECT * from alumnos;