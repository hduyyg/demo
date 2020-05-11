package com.example.demo;

import com.example.demo.demo4.ImportSelectorTest;
import com.example.demo.demo4.ImportTest;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Import;

@Import({ImportTest.class, ImportSelectorTest.class})
@SpringBootApplication
public class DemoApplication {

    public static void main(String[] args) {
        SpringApplication.run(DemoApplication.class, args);
    }

}
