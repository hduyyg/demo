//package com.example.demo.test1;
//
//import org.quartz.*;
//import org.quartz.impl.StdSchedulerFactory;
//import org.springframework.beans.factory.InitializingBean;
//import org.springframework.stereotype.Component;
//
//@Component
//public class Start implements InitializingBean {
//
//    @Override
//    public void afterPropertiesSet() throws Exception {
//        // job描述
//        JobDetail jobDetail = JobBuilder.newJob(WelcomeJob.class)
//                .withIdentity("jobDetail", "jobDetailGroup")
//                .build();
//        // 触发器
//        Trigger trigger = TriggerBuilder.newTrigger()
//                .withIdentity("trigger", "triggerGroup")
//                .startNow()
//                .build();
//
//        Scheduler scheduler = StdSchedulerFactory.getDefaultScheduler();
//        scheduler.scheduleJob(jobDetail, trigger);
//        scheduler.start();
//
//        try {
//            Thread.sleep(1000);
//        } catch (InterruptedException e) {
//            scheduler.shutdown();
//        }
//    }
//}
