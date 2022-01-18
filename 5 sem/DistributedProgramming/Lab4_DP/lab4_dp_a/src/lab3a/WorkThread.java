package lab3a;

public class WorkThread extends Thread {
    private int task;
    private Data data;

    public WorkThread(int task, Data data){
        this.task = task;
        this.data = data;
    }

    @Override
    public void run(){
        switch(task){
            case 1: findPhoneByName();
            break;
            case 2: findNameByPhone();
            break;
            case 3: RWAccounts();
            break;
            default:
                System.out.println("There is no task number like this.");
        }
    }

    private void findPhoneByName() {
        String nameForFind = "Dmytro";
       // while(true){
            data.lockRead();
            System.out.println("Searching phone by name.");
            for(Account account: data.accounts){
                if(account.getName().equals(nameForFind))
                    System.out.println("Founded by searchin phone by name " + account.toString());
            }
            try {Thread.sleep(5000);}
            catch (InterruptedException e) {e.printStackTrace();}
            System.out.println("Searching phone by name is finished");
            data.unlockRead();
        //}
    }

    private void findNameByPhone() {
        String phoneNumberForFind = "+380111111111";
        //while(true) {
            data.lockRead();
            System.out.println("Searching name by phone.");
            for (Account account : data.accounts) {
                if (account.getPhoneNumber().equals(phoneNumberForFind))
                    System.out.println("Founded in searchin name by phone " + account.toString());
            }
            try {Thread.sleep(5000);}
            catch (InterruptedException e) {e.printStackTrace();}
            System.out.println("Searching name by phone is finished.");
            data.unlockRead();
        //}
    }

    private void RWAccounts(){
        Account a1 = new Account("Stephen", "Hawking", "William", "paradise");
        Account a2 = new Account("Stepan", "Bandera", "Andriy", "1909-1959");
        boolean tt = false;

        //while(true){
            data.lockWrite();
            System.out.println("Writing/Deleting accounts.");
            if(tt) data.accounts.add(a1);
            else data.accounts.remove(a1);

            try {Thread.sleep(5000);}
            catch(InterruptedException e){e.printStackTrace();}
            System.out.println("Writing/Deleting accounts is finished.");
            data.unlockWrite();

            try{Thread.sleep(1000);}
            catch (InterruptedException e){e.printStackTrace();}

            data.lockWrite();
            System.out.println("Writing/Deleting accounts.");
            if(tt) data.accounts.add(a2);
            else data.accounts.remove(a2);

            try {Thread.sleep(5000);}
            catch(InterruptedException e){e.printStackTrace();}
            System.out.println("Writing/Deleting accounts is finished.");
            data.unlockWrite();
        //}
    }
}
