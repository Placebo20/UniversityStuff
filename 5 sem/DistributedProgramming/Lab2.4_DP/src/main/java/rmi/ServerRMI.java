package rmi;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class ServerRMI {
    public static void main(String[] args) {
        try
        {
            Registry r = LocateRegistry.createRegistry(1099);
            NewspaperableImpl server = new NewspaperableImpl();
            r.rebind("SayHello", server);
            System.out.println("Server started!");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
}

