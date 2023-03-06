import java.io.*;
import java.net.*;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class cliente {
    public static void main(String[] args) throws IOException {
        
        if (args.length != 2) {
            System.err.println(
                "Uso desde consola: java Cliente_de_Eco <nombre de host (computadora)> <numero puerto>");
            System.exit(1);
        }

        String nombreHost = args[0];
        int numeroPuerto = Integer.parseInt(args[1]);

        try (
            Socket socketEco = new Socket(nombreHost, numeroPuerto); //Socket del cliente
            PrintWriter escritor = new PrintWriter(socketEco.getOutputStream(), true);
            
            BufferedReader lector = new BufferedReader(new InputStreamReader(socketEco.getInputStream())); //Lector de entrada desde el servidor
            BufferedReader teclado = new BufferedReader( new InputStreamReader(System.in)) //Lector del teclado
        ) {
            String EcoServidor,Escritura;
            
            while ((Escritura = teclado.readLine()) != null) {
                ByteBuffer bb = ByteBuffer.wrap(Escritura.getBytes());
                bb.order(ByteOrder.BIG_ENDIAN); //MSB codificado primero
                
                escritor.println((char)bb.get());
                
                EcoServidor = lector.readLine();
                System.out.println("El eco del servidor dice:  " + EcoServidor);//Imprime el mensaje recibido
            }
        } catch (UnknownHostException e) {
            System.err.println("No conozco al host " + nombreHost);
            System.exit(1);
        } catch (IOException e) {
            System.err.println("no se pudo obtener E/S para la conexion " +
                nombreHost);
            System.exit(1);
        } 
    }
}
