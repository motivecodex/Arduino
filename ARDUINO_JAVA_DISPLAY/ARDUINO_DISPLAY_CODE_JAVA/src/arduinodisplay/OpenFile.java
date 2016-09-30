package arduinodisplay;


/**
 *
 * @author Naam: Shahin Mokhtar Moshfeghi HvA: Id@500669336 Klas: IS202
 */

import java.io.File;
import java.util.Scanner;
import javax.swing.JFileChooser;

public class OpenFile {

    // Declare Variable
    JFileChooser fileChooser = new JFileChooser();
    StringBuilder sb = new StringBuilder();

    public void PickMe() throws Exception {
        
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
}
