package com.example.demo.demo4;

import org.springframework.context.annotation.ImportSelector;
import org.springframework.core.type.AnnotationMetadata;

public class ImportSelectorTest implements ImportSelector {

    // ImportSelector接口定义的方法
    // Spring容器会传入当前标记@Import的类的全部注解元数据，用于读取注解中的配置
    // 返回需要注册的全类名，Spring容器会自动注册这些类
    // 注意：不能返回null
    @Override
    public String[] selectImports(AnnotationMetadata importingClassMetadata) {
        // 返回想要注册的全类名
        return new String[] { ImportBeanTest.class.getName() };
    }

}