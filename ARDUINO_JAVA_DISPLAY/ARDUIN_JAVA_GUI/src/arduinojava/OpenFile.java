package arduinojava;

/**
 * @author Name: Shahin Mokhtar Moshfeghi HvA Id: 500669336 Class: IS202
 */
import java.io.File;
import java.util.ArrayList;
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
//    StringBuilder data = new StringBuilder();
    String data = "";
    String delimiter = ";";
    //maak een arrayList
    //String[] value = new String[30];
    ArrayList<User> userList = new ArrayList<User>();
    String lastName;
    int sizeArray = 0;
    File file;

    /**
     * Opencsv csv (comma-seperated values) reader
     */
    public void openCsv() {
        try {

            if (fileChooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
                // Get file
                file = fileChooser.getSelectedFile();

                // Create a scanner for the file
                Scanner input = new Scanner(file);

                // Retrieve but ignore first row (column titles)
                data = input.nextLine();

                // Read from input
                while (input.hasNext()) {
                    // Gets whole row
                    data = input.nextLine();

                    int column = 0;
                    String cellName = new String();

                    // Create user
                    User user = new User();

                    for (String cell : data.split(delimiter)) {
                        // Fill the User object
                        switch (column) {
                            case 0:
                                cellName = "University: ";
                                user.setUniversity(cell);
                                column++;
                                break;
                            case 1:
                                cellName = "First name: ";
                                user.setFirstName(cell);
                                column++;
                                break;
                            case 2:
                                cellName = "Lastname: ";
                                user.setLastName(cell);
                                column++;
                                break;
                            case 3:
                                cellName = "Field of study:  ";
                                user.setFieldOfStudy(cell);
                                break;
                        }
                    }

                    // Add the user to the userList
                    userList.add(user);
                }

                // Print complete user list:
                for (User user : userList) {
                    user.printUser();
                    System.out.println();
                }

                input.close();

            } else {
                sb.append("No file was selected");
            }

        } catch (Exception e) {
            System.out.println("hier gaat het fout");
            System.out.println(e);
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
