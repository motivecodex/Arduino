package arduinojava;

/**
 * @author Name: Shahin Mokhtar Moshfeghi HvA Id: 500669336 Class: IS202
 */
import gnu.io.*;
import java.awt.Color;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.TooManyListenersException;

public class ArduinoJava implements SerialPortEventListener {

    /**
     * Passed from GUI
     */
    GUI window = null;

    /**
     * For containing the ports that will be found
     */
    private Enumeration ports = null;

    /**
     * Map the port names to CommPortIdentifiers
     */
    private HashMap portMap = new HashMap();

    /**
     * Object that contains the opened port
     */
    private CommPortIdentifier selectedPortIdentifier = null;
    private SerialPort serialPort = null;

    /**
     * Input and output streams for sending and receiving data
     */
    private InputStream input = null;
    private OutputStream output = null;

    /**
     * Boolean flag for enabling and disabling buttons depending on whether the
     * program is connected to a serial port or not
     */
    private boolean bConnected = false;

    /**
     * Device COM
     */
    String devCom;

    /**
     * Timeout value for connecting with the port
     */
    final static int TIMEOUT = 2000;

    /**
     * Ascii values for for certain things
     */
    final static int SPACE_ASCII = 32;
    final static int DASH_ASCII = 45;
    final static int NEW_LINE_ASCII = 10;

    /**
     * String for recording what goes on in the program. This string is written
     * to the GUI
     */
    String logText = "";

    /**
     * Passed from GUI
     */
    public ArduinoJava(GUI window) {
        this.window = window;
    }

    /**
     * search for all the serial ports. Adds all the found ports to a combo box
     * on the GUI
     */
    public void searchForPorts() {
        ports = CommPortIdentifier.getPortIdentifiers();

        while (ports.hasMoreElements()) {
            CommPortIdentifier curPort = (CommPortIdentifier) ports.nextElement();

            /**
             * Get only serial ports
             */
            if (curPort.getPortType() == CommPortIdentifier.PORT_SERIAL) {
                window.cboxPorts.addItem(curPort.getName());
                portMap.put(curPort.getName(), curPort);
            }
        }
    }

    /**
     * connect to the selected port in the combo box. pre: ports are already
     * found by using the searchForPorts method. post: the connected comm port
     * is stored in commPort, otherwise, an exception is generated
     */
    public void connect() {
        /**
         * Get selected item in the combo box and put that in String
         * selectedPort
         */
        String selectedPort = (String) window.cboxPorts.getSelectedItem();
        selectedPortIdentifier = (CommPortIdentifier) portMap.get(selectedPort);

        CommPort commPort = null;

        try {
            //the method below returns an object of type CommPort
            commPort = selectedPortIdentifier.open("TigerControlPanel", TIMEOUT);
            //the CommPort object can be casted to a SerialPort object
            serialPort = (SerialPort) commPort;

            //for controlling GUI elements
            setConnected(true);

            //logging
            logText = selectedPort + " opened successfully.";
            window.txtLog.setForeground(Color.black);
            window.txtLog.append(logText + "\n");
        } catch (PortInUseException e) {
            logText = selectedPort + " is in use. (" + e.toString() + ")";
            window.txtLog.setForeground(Color.RED);
            window.txtLog.append(logText + "\n");
        } catch (Exception e) {
            logText = "Failed to open " + selectedPort + "(" + e.toString() + ")";
            window.txtLog.append(logText + "\n");
            window.txtLog.setForeground(Color.RED);
        }
    }

    /**
     * Open the input and output streams. pre: an open port. post: initialized
     * input and output streams for use to communicate data
     */
    public boolean initIOStream() {
        //return value for wetter opening the streams is successful or not
        boolean successful = false;

        try {
            /**
             * get input and output streams and put them in input and output
             */
            input = serialPort.getInputStream();
            output = serialPort.getOutputStream();

            /**
             * write empty data to the Arduino
             */
//            writeData(0, 0);
            successful = true;
            return successful;
        } catch (IOException e) {
            logText = "I/O Streams failed to open. (" + e.toString() + ")";
            window.txtLog.setForeground(Color.red);
            window.txtLog.append(logText + "\n");
            return successful;
        }
    }

    /**
     * Starts the event listener that knows whenever data is available to be
     * read. pre: an open serial port. post: an event listener for the serial
     * port that knows when data is received
     */
    public void initListener() {
        try {
            serialPort.addEventListener(this);
            serialPort.notifyOnDataAvailable(true);
        } catch (TooManyListenersException e) {
            logText = "Too many listeners. (" + e.toString() + ")";
            window.txtLog.setForeground(Color.red);
            window.txtLog.append(logText + "\n");
        }
    }

    /**
     * Disconnect the serial port. pre: an open serial port. post: closed serial
     * port
     */
    public void disconnect() {
        //close the serial port
        try {
            /**
             * write empty data to the Arduino
             */
//            writeData(0, 0);

            serialPort.removeEventListener();
            serialPort.close();
            input.close();
            output.close();
            setConnected(false);

            logText = "Disconnected.";
            window.txtLog.setForeground(Color.red);
            window.txtLog.append(logText + "\n");
        } catch (Exception e) {
            logText = "Failed to close " + serialPort.getName() + "(" + e.toString() + ")";
            window.txtLog.setForeground(Color.red);
            window.txtLog.append(logText + "\n");
        }
    }

    final public boolean getConnected() {
        return bConnected;
    }

    public void setConnected(boolean bConnected) {
        this.bConnected = bConnected;
    }

    /**
     * what happens when data is received. pre: serial event is triggered. post:
     * processing on the data it reads
     */
    public void serialEvent(SerialPortEvent evt) {
        if (evt.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
            try {
                byte singleData = (byte) input.read();

                if (singleData != NEW_LINE_ASCII) {
                    logText = new String(new byte[]{singleData});
                    window.txtLog.append(logText);
                } else {
                    window.txtLog.append("\n");
                }
            } catch (Exception e) {
                logText = "Failed to read data. (" + e.toString() + ")";
                window.txtLog.setForeground(Color.red);
                window.txtLog.append(logText + "\n");
            }
        }
    }

    /**
     * method that can be called to send data. pre: open serial port. post: data
     * sent to the other device
     */
    public void writeData(int companyname) {
        try {
            output.write(companyname);
            output.flush();
        } catch (Exception e) {
            logText = "Failed to write data. (" + e.toString() + ")";
            window.txtLog.setForeground(Color.red);
            window.txtLog.append(logText + "\n");
        }
    }

    void writeData(char[] charA) {
        throw new UnsupportedOperationException("Not supported yet.");
    }
}
