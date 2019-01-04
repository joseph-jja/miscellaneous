package com.ja.jwmail.servlets;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;


import com.ja.jwmail.formbeans.BaseFormBean;

/**
 * default action for maping basic actions that do nothing
 * like going to the log in screen
 * 
 * @author Joseph Acosta
 *
 */
public class DefaultAction extends BaseAction {

	@Override
	public String processRequest(BaseFormBean form, HttpServletRequest request,
			HttpServletResponse response, HttpSession session) throws Exception {
		
		return BaseAction.SUCCESS;
	}

}
