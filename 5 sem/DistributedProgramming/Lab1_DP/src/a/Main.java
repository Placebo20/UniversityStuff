package a;

import javax.swing.*;

class Slide extends JSlider {
    public Slide() {
        super(0,100);
    }
    
    synchronized public void Increase(int increment){
        setValue((int)getValue() + increment);
    }
}

class myThread extends Thread {
    private int increment;
    private Slide mySlider;
    private int count;
    private static int BOUND = 1000000;
    private static int THREAD_COUNTER = 0;
    private int curNum;

    public myThread(Slide mySlider, int increment, int priority) {
        this.mySlider = mySlider;
        this.increment = increment;
        curNum = ++THREAD_COUNTER;
        setPriority(priority);
    }

    @Override
    public void run() {
        while(!interrupted()){
            int val = (int)(mySlider.getValue());
            ++count;
            if(count > BOUND){
                mySlider.Increase(increment);
                count = 0;
            }
        }
    }

    public JPanel GetJPanel() {
        JPanel panel = new JPanel();
        JLabel label = new JLabel("Thread #" + curNum + ", Increment = " + increment);
        SpinnerModel sModel = new SpinnerNumberModel(getPriority(), Thread.MIN_PRIORITY, Thread.MAX_PRIORITY, 1);
        JSpinner Spinner = new JSpinner(sModel);
        Spinner.addChangeListener(e->{setPriority((int)(Spinner.getValue()));});
        panel.add(label);
        panel.add(Spinner);
        return panel;
    }
}

public class Main {
    public static int SEMAPHORE = 0;
    static Thread T1, T2;
    public static void main(String[] args) {
        JFrame Lab1_DP = new JFrame();
        Lab1_DP.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Lab1_DP.setSize(500, 500);
        Slide mySSlider = new Slide();

        myThread Tthread1 = new myThread(mySSlider, +1, Thread.NORM_PRIORITY);
        myThread TThread2 = new myThread(mySSlider, -1, Thread.NORM_PRIORITY);

        JButton startBTTN = new JButton("ПУСК");
        startBTTN.addActionListener(e -> {
            Tthread1.start();
            TThread2.start();
            startBTTN.setEnabled(false);
        });
        JPanel Lab1_DPPanel = new JPanel();
        Lab1_DPPanel.setLayout(new BoxLayout(Lab1_DPPanel, BoxLayout.Y_AXIS));

        Lab1_DPPanel.add(Tthread1.GetJPanel());
        Lab1_DPPanel.add(TThread2.GetJPanel());
        Lab1_DPPanel.add(mySSlider);

        JPanel jPanel = new JPanel();
        jPanel.add(startBTTN);
        Lab1_DPPanel.add(jPanel);

        Lab1_DP.setContentPane(Lab1_DPPanel);
        Lab1_DP.setVisible(true);

    }
}