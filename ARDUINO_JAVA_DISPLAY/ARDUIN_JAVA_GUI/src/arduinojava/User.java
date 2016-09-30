/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package arduinojava;

//to write data to a .csv file
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

/**
 *
 * @author Arjan
 */
public class User {
    
    //variables for the user class:
    private String university = new String();
    private String firstName = new String();
    private String lastName = new String();
    private String fieldOfStudy = new String();
    
    //user information array
    private final String userArray[] = {university, firstName, lastName, fieldOfStudy};
    
    public User()
    {
        
    }
    
    //setter methods
    void setUniversity(String inputUniversity)
    {
        university = inputUniversity;
    }
    void setFirstName(String inputFirstName)
    {
        firstName = inputFirstName;
    }
    void setLastName(String inputLastName)
    {
        lastName = inputLastName;
    }
    void setFieldOfStudy(String inputFieldOfStudy)
    {
        fieldOfStudy = inputFieldOfStudy;
    }
    
    //getter methods
    String getUniversity()
    {
        return university;
    }
    String getFirstName()
    {
        return firstName;
    }
    String getLastName()
    {
        return lastName;
    }
    String getFieldOfStudy()
    {
        return fieldOfStudy;
    }
    
    String[] getUserArray()
    {
        return userArray;
    }
    
    //print the user to the console
    void printUser()
    {
        System.out.println("User: " + firstName + " " + lastName);
        System.out.println("University: " + university);
        System.out.println("Field of study: " + fieldOfStudy);
    }
    
    //string of the user information
    String getUserString()
    { 
        String userString = new String();
        userString = userString.concat("User: " + firstName + " " + lastName + "\n"); //user name
        userString = userString.concat("University: " + university + "\n"); //university
        userString = userString.concat("Field of study: " + fieldOfStudy + "\n"); //field of study
        return userString;
    }
    
    void writeUserToCsvFile(File file)
    {
        try
        {
            //create file writer, true for appending in the file
            FileWriter writer = new FileWriter(file,true);
            
            //go to a new line
            writer.append(';');
            writer.append('\n');
            
            writer.append(university);
            writer.append(';');
            writer.append(firstName);
            writer.append(';');
            writer.append(lastName);
            writer.append(';');
            writer.append(fieldOfStudy);
            writer.append('\n');
            
            writer.flush();
            writer.close();
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
    }
}
