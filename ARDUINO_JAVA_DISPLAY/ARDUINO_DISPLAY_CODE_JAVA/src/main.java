
import arduinodisplay.DisplayForm;

/**
 *
 * @author Naam: Shahin Mokhtar Moshfeghi HvA: Id@500669336 Klas: IS202
 */
public class main {

    public static void main(String[] args) {
        Thread t = new Thread() {
            public void run() {
                // the following line will keep this app alive for 1000 seconds,
                // waiting for events to occur and responding to them (printing incoming messages to console).
                try {
                    Thread.sleep(1000000);
                } catch (InterruptedException ie) {
                }
            }
        };
        t.start();
        System.out.println("Started");

        // Start GUI
        DisplayForm gui = new DisplayForm();
        gui.setVisible(true);
    }
}
