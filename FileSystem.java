
//javac -h . FileSystem.java
import java.util.*;

public class FileSystem {

    static {
        // System.out.println(System.getProperty("java.library.path"));

        System.loadLibrary("FileSys");
    }

    private native void nativeMethod(String path);

    private void callback() {
        System.out.println("Have a good day :)");
        // System.out.println(System.getProperty("java.library.path"));
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("\nEnter path eg: D:\\someFolder\\\n");
        String path = sc.nextLine();
        FileSystem cObj = new FileSystem();
        cObj.nativeMethod(path);
         sc.close();
    }
}