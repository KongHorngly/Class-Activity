import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class multi_thread {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java multi_thread <number_of_threads>");
            return;
        }

        int num = Integer.parseInt(args[0]);

        ExecutorService pool = Executors.newCachedThreadPool();

        for (int i = 0; i < num; i++) {
            pool.execute(new SimpleTask());
        }

        pool.shutdown();
    }
}
