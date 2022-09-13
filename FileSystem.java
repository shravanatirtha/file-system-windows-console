
// Steps to execute
// javac -h . FileSystem.java
// gcc -I"C:\Program Files\Java\jdk1.8.0_202\include" -I"C:\Program Files\Java\jdk1.8.0_202\include\win32" -shared -o FileSys.dll FileSystem.c
// java FileSystem

/*
 * 
 * 1. Locate identifier of Long class with FindClass
    2. Locate identifier of its constructor which accepts primitive type long with GetMethodID
    3. Create new java Long object by passing irno as argument to its constructor with NewObjectA

Other variables must be converted to their corresponding java types: c++ double to java Double, 
c++ char[] to java String or to java char[] and so on.

If you are going to pass a lot of such primitive objects to and from java, then I suggest that you
 use some serialization library, such as google protobuf. You fill in protobuf message in java, 
 serialize it into byte array and pass this byte array into java. In java, you deserialize it and 
 get nice java object. When you need to add more fields, then you won't need 
 to write any more error-prone JNI code.
 * 
 * 
 * 
 * 
 * 
 * 
 */

import java.util.*;
// import java.sql.Connection;
// import java.sql.DriverManager;
// import java.sql.ResultSet;
// import java.sql.SQLException;
// import java.sql.Statement;

public class FileSystem {

    static {
        System.loadLibrary("FileSys");
    }

    private native FileInfo fileSystem(String path);

    public static void main(String[] args) {
        FileSystem fs = new FileSystem();
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the path");
        String path = sc.nextLine();
        FileInfo fi = fs.fileSystem(path);
        System.out.println("File Name: " + fi.getcFileName());
        System.out.println("Directory Count: " + fi.getDirectory_count());
        System.out.println("File Count: " + fi.getFile_count());
        System.out.println("File Size: " + fi.getnFileSizeLow());
        // fs.fileSystem(path);
        // FileInfo fi = fs.fileSystem(path);
        // System.out.println("File Name: " + fi.getcFileName());
        // System.out.println("Directory Count: " + fi.getDirectory_count());
        // System.out.println("File Count: " + fi.getFile_count());
        // System.out.println("File Size: " + fi.getnFileSizeLow());
        sc.close();
    }

}
// private static String jdbc_class = "com.mysql.cj.jdbc.Driver";
// private static String url = "jdbc:mysql://localhost:3306/file_info";
// private static String user = "root";
// private static String password = "";

// private native FileInfo fileSystemUtility(String path);

// private void callback() {
// System.out.println("Have a good day :)");
// }

// public static void main(String[] args) {
// Scanner sc = new Scanner(System.in);
// System.out.println("\nEnter path eg: D:\\someFolder\\\n");
// String path = sc.nextLine();
// FileSystem fs = new FileSystem();
// FileInfo fi = fs.fileSystemUtility(path);
// System.out.println(" cFileName: " + fi.getcFileName());
// System.out.println("dwFileAttributes: " + fi.getDwFileAttributes());
// System.out.println("ftCreationTime: " + fi.getFtCreationTime());
// System.out.println("ftLastAccessTime: " + fi.getFtLastAccessTime());
// System.out.println("ftLastWriteTime: " + fi.getFtLastWriteTime());
// System.out.println("directory_count: " + fi.getDirectory_count());
// System.out.println("file_count: " + fi.getFile_count());
// System.out.println("nFileSizeLow: " + fi.getnFileSizeLow());
// sc.close();
// }
// }
// FileSystem fs = new FileSystem();
// FileInfo fi = fs.fileSystemUtility(path);
// System.out.println("Path: " + fi.getPath());
// System.out.println("Subdirectories: " + fi.getSubdirectories());
// System.out.println("Files: " + fi.getFiles());
// System.out.println("Size: " + fi.getSize());
// fs.callback();
// try {
// Class.forName(jdbc_class);
// Connection con = DriverManager.getConnection(url, user, password);
// Statement stmt = con.createStatement();
// String sql = "INSERT INTO file_info (path, subdirectories, files, size)
// VALUES ('" + fi.getPath() + "', "
// + fi.getSubdirectories() + ", " + fi.getFiles() + ", " + fi.getSize() + ")";
// stmt.executeUpdate(sql);
// con.close();
// } catch (ClassNotFoundException | SQLException e) {
// e.printStackTrace();
// }
// }
// }

// FileInfo fileInfo = new FileSystem().fileSystemUtility(path);
// fileInfo.setPath(path);
// System.out.println(fileInfo);
// try {
// Class.forName(jdbc_class);
// Connection con = DriverManager.getConnection(url, user, password);
// Statement stmt = con.createStatement();
// String sql = "INSERT INTO file_info (path, subdirectories, files, size)
// VALUES ('" + fileInfo.getPath() + "', " + fileInfo.getSubdirectories() + ", "
// + fileInfo.getFiles() + ", " + fileInfo.getSize() + ")";
// stmt.executeUpdate(sql);
// con.close();
// } catch (ClassNotFoundException | SQLException e) {
// e.printStackTrace();
// }
// }
// // System.out.println("Path: " + fileInfo.getPath());
// // System.out.println("Subdirectories: " + fileInfo.getSubdirectories());
// // System.out.println("Files: " + fileInfo.getFiles());
// // System.out.println("Size: " + fileInfo.getSize());
// // try {
// // Class.forName(jdbc_class);
// // Connection conn = DriverManager.getConnection(url, user, password);
// // Statement stmt = conn.createStatement();
// // String query = "insert into directory values('" + fileInfo.getPath() +
// "'," + fileInfo.getSubdirectories()
// // + ","
// // + fileInfo.getFiles() + "," + fileInfo.getSize() + ");";
// // stmt.executeUpdate(query);
// // stmt.close();
// // conn.close();
// // } catch (ClassNotFoundException e) {
// // System.out.println("MySQL driver class not found");
// // e.printStackTrace();
// // } catch (SQLException e) {
// // System.out.println("Error occurred while executing query ");
// // e.printStackTrace();
// // }
// sc.close();
// }

// }