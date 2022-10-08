
// Steps to execute
// javac -h . FileSystem.java
// gcc -I"C:\Program Files\Java\jdk1.8.0_333\include" -I"C:\Program Files\Java\jdk1.8.0_333\include\win32" -shared -o FileSyst.dll FileSystem.c
// java FileSystem

/*
 * 
 * 1. Locate identifier of Integer class with FindClass
    2. Locate identifier of its constructor which accepts primitive type Integer with GetMethodID
    3. Create new java Integer object by passing irno as argument to its constructor with NewObjectA

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
// file utility class
// jdbc class
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;

public class FileSystem {
    // load library path of dll
    static {
        System.loadLibrary("FileSyst");
    }

    // native method
    private native FileInfo fileSystem(String path);

    private native String[] filePath(String path, int dir_count);

    // jdbc connectivity variables
    private static String jdbc_class = "com.mysql.cj.jdbc.Driver";
    private static String url = "jdbc:mysql://localhost:3306/file_info";
    private static String user = "root";
    private static String password = "";

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        try {

            FileSystem fs = new FileSystem();
            System.out.println("Enter the path");
            String inputpath = sc.nextLine();
            String path = inputpath.toLowerCase();
            // calling native method
            FileInfo fi = fs.fileSystem(path);
            int n = fi.getDirectory_count();
            System.out.println(n);
            String[] paths = fs.filePath(path, n);
            for (int i = 0; i < n; i++) {
                System.out.println(i + " " + paths[i]);
            }
            for (int i = 0; i < n; i++) {
                if (paths[i] != null) {
                    fi = fs.fileSystem(paths[i].toLowerCase());
                    String size = "";
                    int sizeInBytes = fi.getnFileSizeLow();
                    if (sizeInBytes < 1024) {
                        size = Integer.toString(sizeInBytes) + " Bytes";
                    } else if (sizeInBytes >= 1024 && sizeInBytes < 1048576) {
                        size = Integer.toString(sizeInBytes / 1024) + " KB";
                    } else if (sizeInBytes >= 1048576 && sizeInBytes < 1073741824) {
                        size = Integer.toString(sizeInBytes / 1048576) + " MB";
                    } else if (sizeInBytes >= 1073741824) {
                        size = Integer.toString(sizeInBytes / 1073741824) + " GB";
                    }
                    int index = paths[i].lastIndexOf("\\");
                    String dir_name = paths[i].substring(index + 1);
                    String parent_path = paths[i].substring(0, index);
                    Class.forName(jdbc_class);
                    Connection con = DriverManager.getConnection(url, user, password);
                    PreparedStatement stmt = con
                            .prepareStatement("select * from directory WHERE parent_path=? and directory_name=?");
                    stmt.setString(1, parent_path);
                    stmt.setString(2, dir_name);

                    ResultSet rs = stmt.executeQuery();
                    if (rs.next()) {
                        int version = getVersion(parent_path, dir_name);
                        update(parent_path, dir_name, fi, sizeInBytes, size, version + 1);
                    } else {
                        insert(parent_path, dir_name, fi, sizeInBytes, size);
                    }
                    // n = fi.getDirectory_count();
                    con.close();
                }
            }
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (SQLException e) {
            e.printStackTrace();
        } catch (NullPointerException e) {
            System.out.println("Invalid Path");
        } finally {
            sc.close();

        }
    }

    static void insert(String path, String name, FileInfo fi, int sizeInBytes, String size) {
        try {
            Class.forName(jdbc_class);
            Connection con = DriverManager.getConnection(url, user, password);
            PreparedStatement stmt = con.prepareStatement("insert into directory values(?,?,?,?,?,?,?,?)");
            stmt.setString(1, path);
            stmt.setString(2, name);
            stmt.setInt(3, fi.getDirectory_count());
            stmt.setInt(4, fi.getFile_count());
            stmt.setString(5, size);
            stmt.setInt(6, sizeInBytes);
            stmt.setTimestamp(7, new java.sql.Timestamp(new java.util.Date().getTime()));
            stmt.setInt(8, 1);
            stmt.executeUpdate();

            System.out.println("Directory inserted successfully");
            con.close();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (SQLException e) {
            e.printStackTrace();
        }

    }

    static void update(String path, String name, FileInfo fi, int sizeInBytes, String size, int version) {
        try {
            Class.forName(jdbc_class);
            Connection con = DriverManager.getConnection(url, user, password);
            PreparedStatement stmt = con.prepareStatement("insert into directory values(?,?,?,?,?,?,?,?)");
            stmt.setString(1, path);
            stmt.setString(2, name);
            stmt.setInt(3, fi.getDirectory_count());
            stmt.setInt(4, fi.getFile_count());
            stmt.setString(5, size);
            stmt.setInt(6, sizeInBytes);
            stmt.setTimestamp(7, new java.sql.Timestamp(new java.util.Date().getTime()));
            stmt.setInt(8, version);

            stmt.executeUpdate();
            System.out.println("Data updated successfully");
            con.close();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    static int getVersion(String path, String dir_name) {
        int version = 0;
        try {
            Class.forName(jdbc_class);
            Connection con = DriverManager.getConnection(url, user, password);
            PreparedStatement stmt = con
                    .prepareStatement("select count(*) from directory where parent_path=? and directory_name=?");
            stmt.setString(1, path);
            stmt.setString(2, dir_name);
            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                version = rs.getInt(1);
                // System.out.println(version);
            }
            con.close();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return version;
    }
}

// stmt.setString(1, path);
// ResultSet result = stmt.executeQuery();

// if (result.next()) {
// stmt = con.prepareStatement("insert into directory values(?,?,?,?);");
// stmt.setString(1, fi.getcFileName());
// stmt.setInt(2, fi.getDirectory_count());
// stmt.setInt(3, fi.getFile_count());
// stmt.setString(4, size);
// stmt.executeUpdate();
// System.out.println("Data inserted successfully");
// stmt.close();
// } else {
// stmt = con.prepareStatement("update directory set
// subdirectories=?,files=?,size=? where path=?;");
// stmt.setString(1, path);
// stmt.setInt(2, fi.getDirectory_count());
// stmt.setInt(3, fi.getFile_count());
// stmt.setString(4, size);
// stmt.executeUpdate();
// System.out.println("Data updated successfully");
// stmt.close();
// }

// con.close();
// } catch (ClassNotFoundException | SQLException e) {
// e.printStackTrace();
// } finally {
// sc.close();
// }
// }
// }
// stmt.setString(1, path);
// result = stmt.executeUpdate();
// if (result == 0) {
// stmt = con.prepareStatement("insert into file_info.directory
// values(?,?,?,?)");
// stmt.setString(1, fi.getcFileName());
// stmt.setInt(2, fi.getDirectory_count());
// stmt.setInt(3, fi.getFile_count());
// stmt.setString(4, size);
// stmt.executeUpdate();
// if (result == 1) {
// System.out.println("Data inserted successfully");
// } else {
// System.out.println("Data not inserted");
// }
// } else {
// stmt = con.prepareStatement(
// "update directory set path=?, directory_count=?, file_count=?, size=? WHERE
// path=?");
// stmt.setString(1, fi.getcFileName());
// stmt.setInt(2, fi.getDirectory_count());
// stmt.setInt(3, fi.getFile_count());
// stmt.setString(4, size);
// stmt.setString(5, path);
// result = stmt.executeUpdate();
// if (result == 1) {
// System.out.println("Data updated successfully");
// } else {
// System.out.println("Data not updated");
// }
// }

// con.close();
// } catch (ClassNotFoundException | SQLException e) {
// e.printStackTrace();
// } finally {
// sc.close();
// }

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
//

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