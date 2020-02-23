package com.example.demo.controller;

import com.example.demo.dao.UserSuportRecordRepository;
import com.example.demo.dao.model.UserSuportRecord;
import com.example.demo.model.BaseResponse;
import com.google.common.collect.Lists;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.List;

/**
 * 用户支持记录相关
 */
@Controller
@RequestMapping("/user-support")
public class UserSuportController {

    @Autowired
    private UserSuportRecordRepository userSuportRecordRepository;

    /**
     * 用户支持页面
     * @param model
     * @return
     */
    @GetMapping("/index")
    public String recordHtml(Model model) {
        List<UserSuportRecord> records = userSuportRecordRepository.findAll();
        records.sort(((o1, o2) -> o2.getCreateTime().compareTo(o1.getCreateTime())));
        model.addAttribute("records", records);

        return "userSupportRecord/userSupportRecord";
    }

    /**
     * 添加用户支持记录
     * @param record
     * @return
     */
    @ResponseBody
    @PostMapping("/save")
    public BaseResponse saveRecord(UserSuportRecord record) {
        userSuportRecordRepository.save(record);
        return BaseResponse.success();
    }

    /**
     * 根据id更新记录
     * @param record
     * @return
     */
    @ResponseBody
    @PostMapping("/update")
    public BaseResponse updateRecordById(UserSuportRecord record) {
        if (record.getId() == null) {
            throw new RuntimeException("用户支持记录更新，id不能为空");
        }
        if (userSuportRecordRepository.findById(record.getId()) == null) {
            throw new RuntimeException("用户支持记录id不存在:" + record.getId());
        }
        userSuportRecordRepository.save(record);
        return BaseResponse.success();
    }

    /**
     * 获取所有记录，按照创建时间降序排序
     * @return
     */
    @ResponseBody
    @GetMapping("/get/all")
    public BaseResponse getAll() {
        List<UserSuportRecord> records = userSuportRecordRepository.findAll();
        records.sort(((o1, o2) -> o2.getCreateTime().compareTo(o1.getCreateTime())));
        return BaseResponse.success(records);
    }
}
