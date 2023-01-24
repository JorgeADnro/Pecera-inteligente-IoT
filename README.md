# ProjectsIoT2023

## Integrantes
1. Jorge Luis Ayala Manrique
2. José Armando Gutiérrez Rodríguez
3. Carlos Eduardo Mata Rojas
4. Victor Andrés Garay Montes

## Objetivo general
En este proyecto se pretende diseñar y crear una pecera inteligente, esta será controlada con una aplicación movil con capacidad
de dispensar comida automáticamente a una hora programada o cuando el usuario lo requiera, gestionando también la cantidad de comida 
que será dispensada. Esta pecera contendrá un modo nocturno que consiste en que cuando se detecta poca luz, se encenderá
una serie de luces led blanca al contorno de la pecera, además de contar con una serie RGB para personalizar su diseño; también contendrá un aireador
que puede ser encendido debido a gestión del usuario o cuando detecte temperaturas ligeramente altas; todo esto podrá ser programable desde
la aplicación móvil.

## Tabla de Software utilizado
| Id | Software | Version | Tipo |
|----|----------|---------|------|
|  1  |  Arduino  |  2.0.1  |  IDE  |
|  2  |  Visual Studio Code  |  1.71.2  |  IDE  |
|  3  |  Node-Red  |  3.0  |  Servicio  |


## Tabla con el hardware utilizado
| Id | Componente | Descripción | Imagen | Cantidad | Costo total |
|----|------------|-------------|--------|----------|-------------|
|  1  |  ESP32  |  El módulo ESP32 es una solución de Wi-Fi/Bluetooth todo en uno, integrada y certificada que proporciona no solo la radio inalámbrica, sino también un procesador integrado con interfaces para conectarse con varios periféricos  |  ![image](https://www.sigmaelectronica.net/wp-content/uploads/2019/03/ESP-32.jpg)|      1    |     $150        |
|   2 |      Sensor De Luz Sensor Fotoresistivo      |      Un sensor fotoeléctrico o fotocélula es un dispositivo electrónico que responde al cambio en la intensidad de la luz.       |    ![image](https://http2.mlstatic.com/D_Q_NP_722260-MLM40766811613_022020-AB.webp)    |    1      |     $57        |
|  3  |       Oky Sensor de Temperatura Contra Agua     |     Sensor de temperatura a prueba de agua que utiliza el chip DS18B20 con una interfaz de bus simple. Gracias a que tiene un encapsulado de acero inoxidable de 6 mm x 50 mm, es resistente al agua, a la humedad y al óxido.        |    ![image](https://www.cyberpuerta.mx/img/product/M/CP-OKY-OS-30651-1.jpg)    |     1     |       $83      |
|  4  |   Tira Luces Led Bluetooth Control App Usb Impermeable Rgb 3m  |     Es una tira de LED que puede cambiar de color usando un controlador. Los diferentes colores se obtienen mezclando los 3 colores primarios rojo, verde y azul, de ahí la abreviatura RGB. Estos 3 colores están presentes en el mismo chip.    |   ![image](https://http2.mlstatic.com/D_NQ_NP_732280-CBT50066636636_052022-O.webp)   |   1  |  $187   |
|  5  |   Lomas Aqua Jet Bomba de Aire de 5 Galones para Peceras y/o Acuario  |     Una bomba de aire o aireador, sirve básicamente para garantizarnos de que no exista una barrera que bloquee el intercambio de oxígeno y dióxido de carbono en el acuario.    |   ![image](https://m.media-amazon.com/images/I/61NWypyg2UL._AC_SX466_.jpg)  |   1  |  $95   |
|  6  |   Pecera cristal  |     Pecera de cristal rectangular    |   ![image](https://m.media-amazon.com/images/I/71cLcaNgpyL.__AC_SX300_SY300_QL70_ML2_.jpg)  |   1  |  $0   |
|  7  |   Servo  |     Servomotor Mg995 15kg Arduino    |   ![image](https://http2.mlstatic.com/D_NQ_NP_681898-MLM52931247115_122022-O.webp)  |   1  |  $0   |

## Tabla de historias de usuario
| Id | Historia de usuario | Prioridad | Estimación | Como probarlo | Responsable |
|----|---------------------|-----------|------------|---------------|-------------|
| 1  | Quiero darle de comer a mis peces cada cierto tiempo manual y automáticamente. |   Alta        |      2 a 3 semanas      |        Esperar a la hora programada o activarlo desde la aplicación móvil       |      Jorge Luis Ayala Manrique       |
| 2  | Cómo usuario quiero encender el airador cada que sea requerido. |    Alta       |    2 a 3 semanas         |      Aumentar la temperatura del ambiente         |       Cristian Emmanuel Gutiérrez Díaz      |
| 3  | Como usuario quiero conocer las condiciones de la pecera. |      Media     |       2 a 3 semanas     |         Revisar la aplicación móvil      |      Jorge Luis Ayala Manrique       |
| 4  | Quiero que en la noche se enciendan las luces de la pecera.  |    Media       |      2 a 3 semanas      |      Reducir la cantidad de luz en la habitación         |       Itzel Alessandra Fuentes Cabrera      |

## Prototipo en dibujo
![image](https://github.com/JorgeADnro/Pecera-inteligente-IoT/blob/f7de850efa2439e0d2261c8579b55cab27329e7f/Dibujo.jpeg)
