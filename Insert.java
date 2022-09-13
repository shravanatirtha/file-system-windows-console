import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Insert {
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
            String query = "insert into directory values('e://',1,30,128 );";
            stmt.executeUpdate(query);
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
