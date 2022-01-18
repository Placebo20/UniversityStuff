package b;

import javax.swing.*;

class myThread extends Thread {
    int inc = 0;
    public myThread(int inc){
        this.inc = inc;
    }

    @Override
    public void run(){
        while(Main.SEMAPHORE != 0);
        Main.SEMAPHORE = 1;
        Main.lbl1.setText("Раздел занят!");
        while(!interrupted()) {
            int val = Main.Slider.getValue();
            if((val > 10 && inc < 0) || (val < 90 && inc > 0))
                Main.Slider.setValue(val + inc);
        }
        Main.SEMAPHORE = 0;
        Main.lbl1.setText("Раздел свободен");
    }
}

public class Main {
    static volatile int SEMAPHORE = 0;
    static volatile JSlider Slider;
    static volatile JLabel lbl1;
    static private myThread Tthread1;
    static private myThread TThread2;
    static private JButton Tthread1STARTBTTN;
    static private JButton TThread2STARTBTTN;
    static private JButton Tthread1STOPBTTN;
    static private JButton TThread2STOPBTTN;

    public static void main(String[] args) {
        JFrame Lab1_DP = new JFrame();
        Lab1_DP.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Lab1_DP.setSize(600,500);
        JPanel Lab1_DPPanel = new JPanel();
        Lab1_DPPanel.setLayout(new BoxLayout(Lab1_DPPanel, BoxLayout.Y_AXIS));

        Slider = new JSlider(0,100);
        Lab1_DPPanel.add(Slider);
        lbl1 = new JLabel("Раздел свободен");

        JPanel Tthread1Panel = new JPanel();
        Tthread1STARTBTTN = new JButton("ПУСК1");
        Tthread1STOPBTTN = new JButton("СТОП1");
        Tthread1STOPBTTN.setEnabled(false);
        Tthread1STARTBTTN.addActionListener(e -> {
            Tthread1 = new myThread(+1);
            Tthread1.setPriority(Thread.MIN_PRIORITY);
            Tthread1STOPBTTN.setEnabled(true);
            Tthread1STARTBTTN.setEnabled(false);
            Tthread1.start();
        });
        Tthread1STOPBTTN.addActionListener(e -> {
            Tthread1.interrupt();
            Tthread1STOPBTTN.setEnabled(false);
            Tthread1STARTBTTN.setEnabled(true);
        });
        Tthread1Panel.add(Tthread1STARTBTTN);
        Tthread1Panel.add(Tthread1STOPBTTN);

        JPanel TThread2Panel = new JPanel();
        TThread2STARTBTTN = new JButton ("ПУСК2");
        TThread2STOPBTTN = new JButton("СТОП2");
        TThread2STOPBTTN.setEnabled(false);
        TThread2STARTBTTN.addActionListener(e-> {
            TThread2 = new myThread(-1);
            TThread2.setPriority(Thread.MAX_PRIORITY);
            TThread2STOPBTTN.setEnabled(true);
            TThread2STARTBTTN.setEnabled(false);
            TThread2.start();
        });
        TThread2STOPBTTN.addActionListener(e-> {
            TThread2.interrupt();
            TThread2STOPBTTN.setEnabled(false);
            TThread2STARTBTTN.setEnabled(true);
        });
        TThread2Panel.add(TThread2STARTBTTN);
        TThread2Panel.add(TThread2STOPBTTN);

        Lab1_DPPanel.add(Tthread1Panel);
        Lab1_DPPanel.add(TThread2Panel);

        Lab1_DP.setContentPane(Lab1_DPPanel);
        Lab1_DP.setVisible(true);
    }
}
