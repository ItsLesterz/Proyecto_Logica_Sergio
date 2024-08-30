#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definición de constantes
#define MAX_PRODUCTOS 100
#define MAX_CLIENTES 100
#define MAX_FACTURAS 100
#define MAX_USUARIOS 10

// Estructura para Producto
typedef struct {
    int codigoProducto;
    char nombre[50];
    char categoria[30];
    float precioCompra;
    float precioVenta;
    int cantidadStock;
    char proveedor[50];
} Producto;

// Estructura para Cliente
typedef struct {
    int idCliente;
    char nombre[50];
    char direccion[100];
    char telefono[15];
    char email[50];
} Cliente;

// Estructura para Factura
typedef struct {
    int numeroFactura;
    char fecha[11];  // Formato DD-MM-AAAA
    Cliente cliente;
    Producto productos[10]; // Máximo 10 productos por factura
    int cantidades[10];
    float preciosUnitarios[10];
    float impuestos[10];
    float total;
} Factura;

// Estructura para Usuario
typedef struct {
    char username[20];
    char password[20];
    char rol[10]; // "admin" o "vendedor"
} Usuario;

// Variables globales para almacenamiento
Producto inventario[MAX_PRODUCTOS];
Cliente clientes[MAX_CLIENTES];
Factura facturas[MAX_FACTURAS];
Usuario usuarios[MAX_USUARIOS];

int numProductos = 0;
int numClientes = 0;
int numFacturas = 0;
int numUsuarios = 0;

// Función para agregar un producto al inventario
void agregarProducto() {
    if (numProductos >= MAX_PRODUCTOS) {
        printf("Inventario lleno, no se pueden agregar más productos.\n");
        return;
    }

    Producto nuevoProducto;
    printf("Ingrese el código del producto: ");
    scanf("%d", &nuevoProducto.codigoProducto);
    printf("Ingrese el nombre del producto: ");
    scanf("%s", nuevoProducto.nombre);
    printf("Ingrese la categoría del producto: ");
    scanf("%s", nuevoProducto.categoria);
    printf("Ingrese el precio de compra: ");
    scanf("%f", &nuevoProducto.precioCompra);
    printf("Ingrese el precio de venta: ");
    scanf("%f", &nuevoProducto.precioVenta);
    printf("Ingrese la cantidad en stock: ");
    scanf("%d", &nuevoProducto.cantidadStock);
    printf("Ingrese el proveedor del producto: ");
    scanf("%s", nuevoProducto.proveedor);

    inventario[numProductos] = nuevoProducto;
    numProductos++;

    printf("Producto agregado con éxito.\n");
}

// Función para modificar un producto existente
void modificarProducto() {
    int codigo, i, encontrado = 0;
    printf("Ingrese el código del producto a modificar: ");
    scanf("%d", &codigo);

    for (i = 0; i < numProductos; i++) {
        if (inventario[i].codigoProducto == codigo) {
            encontrado = 1;
            printf("Modificando producto %s...\n", inventario[i].nombre);
            printf("Ingrese el nuevo nombre del producto: ");
            scanf("%s", inventario[i].nombre);
            printf("Ingrese la nueva categoria del producto: ");
            scanf("%s", inventario[i].categoria);
            printf("Ingrese el nuevo precio de compra: ");
            scanf("%f", &inventario[i].precioCompra);
            printf("Ingrese el nuevo precio de venta: ");
            scanf("%f", &inventario[i].precioVenta);
            printf("Ingrese la nueva cantidad en stock: ");
            scanf("%d", &inventario[i].cantidadStock);
            printf("Ingrese el nuevo proveedor del producto: ");
            scanf("%s", inventario[i].proveedor);
            printf("Producto modificado con exito.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Producto con el codigo %d no encontrado.\n", codigo);
    }
}

// Función para eliminar un producto del inventario
void eliminarProducto() {
    int codigo, i, j, encontrado = 0;
    printf("Ingrese el codigo del producto a eliminar: ");
    scanf("%d", &codigo);

    for (i = 0; i < numProductos; i++) {
        if (inventario[i].codigoProducto == codigo) {
            encontrado = 1;
            for (j = i; j < numProductos - 1; j++) {
                inventario[j] = inventario[j + 1];
            }
            numProductos--;
            printf("Producto eliminado con exito.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Producto con el codigo %d no encontrado.\n", codigo);
    }
}

// Función para registrar un cliente
void registrarCliente() {
    if (numClientes >= MAX_CLIENTES) {
        printf("Numero maximo de clientes alcanzado.\n");
        return;
    }

    Cliente nuevoCliente;
    printf("Ingrese el ID del cliente: ");
    scanf("%d", &nuevoCliente.idCliente);
    printf("Ingrese el nombre del cliente: ");
    scanf("%s", nuevoCliente.nombre);
    printf("Ingrese la direccion del cliente: ");
    scanf("%s", nuevoCliente.direccion);
    printf("Ingrese el numero de telefono del cliente: ");
    scanf("%s", nuevoCliente.telefono);
    printf("Ingrese el correo electrónico del cliente: ");
    scanf("%s", nuevoCliente.email);

    clientes[numClientes] = nuevoCliente;
    numClientes++;

    printf("Cliente registrado con exito.\n");
}

// Función para calcular impuestos
float calcularImpuestos(float subtotal) {
    return subtotal * 0.18; // Suponiendo un impuesto del 18%
}

// Función para generar una factura
void generarFactura() {
    if (numFacturas >= MAX_FACTURAS) {
        printf("Numero máximo de facturas alcanzado.\n");
        return;
    }

    Factura nuevaFactura;
    nuevaFactura.numeroFactura = numFacturas + 1;
    printf("Ingrese la fecha (DD-MM-AAAA): ");
    scanf("%s", nuevaFactura.fecha);

    // Selección de cliente
    printf("Ingrese el ID del cliente: ");
    int idCliente;
    scanf("%d", &idCliente);
    int clienteEncontrado = 0;

    for (int i = 0; i < numClientes; i++) {
        if (clientes[i].idCliente == idCliente) {
            nuevaFactura.cliente = clientes[i];
            clienteEncontrado = 1;
            break;
        }
    }

    if (!clienteEncontrado) {
        printf("Cliente no encontrado.\n");
        return;
    }

    // Agregar productos a la factura
    int numProductosFactura;
    printf("Ingrese la cantidad de productos en la factura: ");
    scanf("%d", &numProductosFactura);

    float subtotal = 0.0;
    for (int i = 0; i < numProductosFactura; i++) {
        int codigoProducto, cantidad;
        printf("Ingrese el codigo del producto %d: ", i + 1);
        scanf("%d", &codigoProducto);
        printf("Ingrese la cantidad: ");
        scanf("%d", &cantidad);

        int productoEncontrado = 0;
        for (int j = 0; j < numProductos; j++) {
            if (inventario[j].codigoProducto == codigoProducto && inventario[j].cantidadStock >= cantidad) {
                nuevaFactura.productos[i] = inventario[j];
                nuevaFactura.cantidades[i] = cantidad;
                nuevaFactura.preciosUnitarios[i] = inventario[j].precioVenta;
                nuevaFactura.impuestos[i] = calcularImpuestos(inventario[j].precioVenta * cantidad);
                subtotal += inventario[j].precioVenta * cantidad;
                inventario[j].cantidadStock -= cantidad; // Actualizar inventario
                productoEncontrado = 1;
                break;
            }
        }

        if (!productoEncontrado) {
            printf("Producto no encontrado o stock insuficiente.\n");
            return;
        }
    }

    nuevaFactura.total = subtotal + calcularImpuestos(subtotal);
    facturas[numFacturas] = nuevaFactura;
    numFacturas++;

    printf("Factura generada con éxito.\n");
}

// Función para registrar una venta
void registrarVenta() {
    printf("Registrando una nueva venta...\n");
    generarFactura(); // Generar factura al registrar la venta
}

// Función para generar un reporte de ventas
void generarReporteVentas() {
    printf("Generando reporte de ventas...\n");
    // Implementar lógica para generar reportes diarios, semanales, y mensuales
}

// Función para crear un usuario
void crearUsuario() {
    if (numUsuarios >= MAX_USUARIOS) {
        printf("Numero máximo de usuarios alcanzado.\n");
        return;
    }

    Usuario nuevoUsuario;
    printf("Ingrese el nombre de usuario: ");
    scanf("%s", nuevoUsuario.username);
    printf("Ingrese la contraseña: ");
    scanf("%s", nuevoUsuario.password);
    printf("Ingrese el rol (admin/vendedor): ");
    scanf("%s", nuevoUsuario.rol);

    usuarios[numUsuarios] = nuevoUsuario;
    numUsuarios++;

    printf("Usuario creado con éxito.\n");
}

// Función para autenticar usuario
int autenticarUsuario(char *rolAutenticado) {
    char username[20], password[20];
    printf("Ingrese su nombre de usuario: ");
    scanf("%s", username);
    printf("Ingrese su contraseña: ");
    scanf("%s", password);

    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].username, username) == 0 && strcmp(usuarios[i].password, password) == 0) {
            strcpy(rolAutenticado, usuarios[i].rol); // Guardar el rol del usuario autenticado
            printf("Bienvenido, %s.\n", usuarios[i].username);
            return 1;
        }
    }

    printf("Autenticacion fallida. Usuario o contraseña incorrectos.\n");
    return 0;
}

// Función para mostrar el menú para administradores
void mostrarMenuAdmin() {
    int opcion;
    do {
        printf("\nMenú Administrador\n");
        printf("1. Agregar Producto\n");
        printf("2. Modificar Producto\n");
        printf("3. Eliminar Producto\n");
        printf("4. Registrar Cliente\n");
        printf("5. Registrar Venta\n");
        printf("6. Generar Reporte de Ventas\n");
        printf("7. Crear Usuario\n");
        printf("8. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarProducto();
                break;
            case 2:
                modificarProducto();
                break;
            case 3:
                eliminarProducto();
                break;
            case 4:
                registrarCliente();
                break;
            case 5:
                registrarVenta();
                break;
            case 6:
                generarReporteVentas();
                break;
            case 7:
                crearUsuario();
                break;
            case 8:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 8);
}

// Función para mostrar el menú para vendedores
void mostrarMenuVendedor() {
    int opcion;
    do {
        printf("\nMenú Vendedor\n");
        printf("1. Registro Producto\n");
        printf("2. Registrar Venta\n");
        printf("3. Registrar Cliente\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarProducto();
                break;
            case 2:
                registrarVenta();
                break;
            case 3:
                registrarCliente();
                break;
            case 4:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 4);
}

// Función para mostrar el menú de inicio
void mostrarMenuInicio() {
    int opcion;
    char rol[10];

    do {
        printf("\n---- Log In ----\n");
        printf("1. Crear Usuario\n");
        printf("2. Iniciar Sesion\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                crearUsuario();
                break;
            case 2:
                if (autenticarUsuario(rol)) {
                    if (strcmp(rol, "admin") == 0) {
                        mostrarMenuAdmin();
                    } else if (strcmp(rol, "vendedor") == 0) {
                        mostrarMenuVendedor();
                    } else {
                        printf("Rol desconocido. Acceso denegado.\n");
                    }
                }
                break;
            case 3:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 3);
}

int main() {
    // Crear un usuario por defecto para permitir el acceso inicial
    Usuario admin = {"admin", "admin", "admin"};
    usuarios[numUsuarios++] = admin;
    // Mostrar menú de inicio
    mostrarMenuInicio();
    return 0;
}
