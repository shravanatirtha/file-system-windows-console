//javac -h . FileSystem.java
public class FileSystem {

    static {
        // System.out.println(System.getProperty("java.library.path"));

        System.loadLibrary("FileSys");
    }

    private native void nativeMethod();

    private void callback() {
        System.out.println("Hello from Java");
        // System.out.println(System.getProperty("java.library.path"));
    }

    public static void main(String[] args) {
        FileSystem cObj = new FileSystem();
        cObj.nativeMethod();
    }
}