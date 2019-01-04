package com.ja.jwmail.servlets;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionMessage;

import com.ja.jwmail.common.MailMessage;
import com.ja.jwmail.formbeans.BaseFormBean;
import com.ja.jwmail.formbeans.MailboxMessage;

/**
 * this is used to get a message and display the message content
 * 
 * @author Joseph Acosta
 *
 */
public class ReadMessageAction extends BaseAction {

	@SuppressWarnings("unchecked")
	@Override
	public String processRequest(BaseFormBean form, HttpServletRequest request,
			HttpServletResponse response, HttpSession session) throws Exception {
		
		// get the pop3 service from the session
		List<MailMessage> messages = (List<MailMessage>)session.getAttribute(BaseAction.MAIL_MESSAGES);

		ActionErrors errors = new ActionErrors();
		
		// if we are connected 
		if ( messages != null && messages.size() > 0 ) { 
			
			MailboxMessage mbmsg = (MailboxMessage)form;
			int index = mbmsg.getIndex();
			
			if ( index < 0 || index > messages.size() ) {
				errors.add("read.errors", new ActionMessage("readmail.out.of.range"));
				addErrors(request, errors);				
				return BaseAction.FAILED;
			}
			
			// mark as read
			MailMessage mail = messages.get(index);
			mail.setReadMail(true);

			messages.remove(index);
			messages.add(index, mail);
			
			// this needs to be accessed from the screen
			request.setAttribute(BaseAction.MESSAGE, mail);

			// put in the session
			session.setAttribute(BaseAction.MAIL_MESSAGES, messages);
			
			return BaseAction.SUCCESS;
		}
		
		errors.add("read.errors", new ActionMessage("readmail.no.messages"));
		addErrors(request, errors);
		
		return BaseAction.FAILED;
	}

}
