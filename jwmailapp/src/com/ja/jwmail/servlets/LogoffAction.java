package com.ja.jwmail.servlets;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;


import com.ja.jwmail.formbeans.BaseFormBean;
import com.ja.jwmail.services.POP3Service;

/**
 * action class used to log out of the pop3 server
 * 
 * @author Joseph Acosta
 *
 */
public class LogoffAction extends BaseAction {

	@Override
	public String processRequest(BaseFormBean form, HttpServletRequest request,
			HttpServletResponse response, HttpSession session) throws Exception {
		
		// null out the mail messages in the session
		if ( session.getAttribute(BaseAction.MAIL_MESSAGES) != null ) {
			session.setAttribute(BaseAction.MAIL_MESSAGES, null);
		}

		// null out the auth record in the session also
		if ( session.getAttribute(BaseAction.AUTH_RECORD) != null ) {
			session.setAttribute(BaseAction.AUTH_RECORD, null);
		}

		return BaseAction.SUCCESS;
	}

}
