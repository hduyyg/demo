
public class Test {

    public static void main(String[] args) {
        while (true) {
            for (int i = 0; i < 100000000; i++) {
                test();
            }
            System.out.println("for");
            try {
                Thread.sleep(3000L);
            } catch (Exception ex) {

            }
        }
    }

    private static void test() {
        new Object();
    }
}
