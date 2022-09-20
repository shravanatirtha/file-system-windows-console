import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Test {
    private static String jdbc_class = "com.mysql.cj.jdbc.Driver";
    private static String url = "jdbc:mysql://localhost:3306/file_info";
    private static String user = "root";
    private static String password = "";
    // private static String query = "insert into directory values('E:\\',0,0,0);";

    public static void main(String[] args) {
        // System.out.println(System.getProperty("java.library.path"));
        try {
            Class.forName(jdbc_class);
            Connection conn = DriverManager.getConnection(url, user, password);
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("select * from directory;");
            while (rs.next()) {
                System.out.println(rs.getString(1)); // First Column
                System.out.println(rs.getString(2)); // Second Column
                System.out.println(rs.getString(3)); // Third Column
                System.out.println(rs.getString(4)); // Fourth Column
            }
            rs.close();
            stmt.close();
            conn.close();
        } catch (ClassNotFoundException e) {
            System.out.println("MySQL driver class not found");
            e.printStackTrace();
        } catch (SQLException e) {
            System.out.println("Error occurred while executing query ");
            e.printStackTrace();
        }
    }
}
