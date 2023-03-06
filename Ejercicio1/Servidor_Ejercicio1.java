

import java.net.*; // paquete que contienen clases de red , todo lo necesario para comunicarme en red
import java.io.*; // paquete que contienen clases para E/S teclado y monitor

public class Servidor_Ejercicio1 {
    
    public static void main(String[] args) throws IOException {
        
        if (args.length != 1) { //verifica que se haya escrito el número de puerto a usar
            System.err.println("Uso desde consola:  <numero puerto>");

            System.exit(1);
        }
        
        int numeroPuerto = Integer.parseInt(args[0]);// convertimos el numero de puerto
        
        try (
            ServerSocket socketdelServidor =
                new ServerSocket(Integer.parseInt(args[0]));//se crea un socket para el servidor con el puerto parametrizado
            Socket socketdelCliente = socketdelServidor.accept();//se tiene una instancia de tipo socket para el manejo de esas peticiones   
            PrintWriter escritor =
                new PrintWriter(socketdelCliente.getOutputStream(), true); //instancia para escribir en el stream socketdelCliente           
            BufferedReader lector = new BufferedReader(
                new InputStreamReader(socketdelCliente.getInputStream()));//instancia para leer del stream socketdelCliente
            BufferedReader teclado = new BufferedReader( new InputStreamReader(System.in));
        ) {
            String linealeida, lineaEscrita;
            int pos;
            while ((linealeida = lector.readLine()) != null) {
                lineaEscrita = teclado.readLine(); //se lee desde consola lo que el usuario quiera mandarle al cliente
                escritor.println(lineaEscrita);
            }
        } catch (IOException e) {
            System.out.println(" ocurrio una excepcion cuando intentamos escuchar "
                + numeroPuerto + " o esperando por una conexicon");
            System.out.println(e.getMessage());
        }
    }
}
