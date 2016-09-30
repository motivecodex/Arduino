package arduinojava;

/**
 * @author Name: Shahin Mokhtar Moshfeghi HvA Id: 500669336 Class: IS202
 */
import java.io.File;
import java.util.Scanner;
import javax.swing.JFileChooser;

public class OpenFile {

    /**
     * Passed from GUI
     */
    GUI gui = null;

    // Declare Variable
    JFileChooser fileChooser = new JFileChooser();
    StringBuilder sb = new StringBuilder();

    /**
     * Open text file
     *
     * @throws Exception
     */
    public void openTxtFile() throws Exception {

        if (fileChooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
            // Get file
            File file = fileChooser.getSelectedFile();

            // Create a scanner for the file
            Scanner input = new Scanner(file);

            // Read text from file
            while (input.hasNext()) {
                sb.append(input.nextLine());
                sb.append("\n");
            }
            input.close();
        } else {
            sb.append("No file was selected");
        }
    }

    /**
     * Open image
     *
     * @throws Exception
     */
    public void openImage() throws Exception {
        GUI gui = new GUI();
        if (fileChooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
            JFileChooser chooser = new JFileChooser(".");
        } else {
            sb.append("No image was selected");
        }
    }
}
