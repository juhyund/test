package com.nuri.kepco.util;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import org.jxls.common.Context;
import org.jxls.util.JxlsHelper;


public class ExcelUtil {
	
	public static void makeExcelTemplate(String template_filepath, String filepath, String filename, Object data) throws IOException {
		
		FileControl.create(filepath); // 경로 생성
		
		String target_filepath = filepath + "/" + filename;
		
		try (InputStream is = ExcelUtil.class.getResourceAsStream(template_filepath)) {
			
			try (OutputStream os = new FileOutputStream(target_filepath)) {
				Context context = new Context();
				context.putVar("result", data);
				JxlsHelper.getInstance().processTemplate(is, os, context);
			}
		}
	}
}