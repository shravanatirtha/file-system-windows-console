public class FileInfo {
    private String path;
    private int subdirectories;
    private int files;
    private int size;

    public FileInfo(String path, int subdirectories, int files, int size) {
        this.path = path;
        this.subdirectories = subdirectories;
        this.files = files;
        this.size = size;
    }

    public String getPath() {
        return path;
    }

    public void setPath(String path) {
        this.path = path;
    }

    public int getSubdirectories() {
        return subdirectories;
    }

    public void setSubdirectories(int subdirectories) {
        this.subdirectories = subdirectories;
    }

    public int getFiles() {
        return files;
    }

    public void setFiles(int files) {
        this.files = files;
    }

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;
    }
}
