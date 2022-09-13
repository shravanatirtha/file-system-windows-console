
// Steps to execute
// javac -h . FileSystem.java
// gcc -I"C:\Program Files\Java\jdk1.8.0_202\include" -I"C:\Program Files\Java\jdk1.8.0_202\include\win32" -shared -o FileSys.dll FileSystem.c
// java FileSystem
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

    private native void fileSystem(String path);

    public static void main(String[] args) {
        FileSystem fs = new FileSystem();
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the path");
        String path = sc.nextLine();
        fs.fileSystem(path);
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