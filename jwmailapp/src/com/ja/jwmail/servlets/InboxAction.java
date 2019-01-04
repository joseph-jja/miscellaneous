/**
 * 
 */
package com.ja.jwmail.servlets;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionMessage;

import com.ja.jwmail.common.MailMessage;
import com.ja.jwmail.formbeans.AuthenticationRecord;
import com.ja.jwmail.formbeans.BaseFormBean;
import com.ja.jwmail.services.POP3Service;

/**
 * view the inbox or get all the mail messages 
 * 
 * @author Joseph Acosta
 *
 */
public class InboxAction extends BaseAction {

	@Override
	public String processRequest(BaseFormBean form, HttpServletRequest request,
			HttpServletResponse response, HttpSession session) throws Exception {

		ActionErrors errors = new ActionErrors();

		// get the auth record from session
		AuthenticationRecord authRecord = (AuthenticationRecord)session.getAttribute(BaseAction.AUTH_RECORD);
		
		// if we have an authentication record and a pop3 service object
		// we can connect
		if ( authRecord != null &&  BaseAction.hasText(authRecord.getUsername()) 
					&& BaseAction.hasText(authRecord.getPassword()) 
					&& BaseAction.hasText(authRecord.getPop3MailServer()) ) {
			
			// get the pop3 service from the session
			POP3Service pop3Service = new POP3Service();

			boolean connected = pop3Service.connect(authRecord.getUsername(), 
					authRecord.getPassword(), authRecord.getPop3MailServer(), 
					authRecord.getPop3Port(), authRecord.isApop());

			// if we are connected 
			if ( connected ) {
				// get the messages
				List<MailMessage> messages = pop3Service.getMessages();

				// put in the session
				session.setAttribute(BaseAction.MAIL_MESSAGES, messages);

				// close connection
				pop3Service.disconnect();

				return BaseAction.SUCCESS;
			}			
		}	
		errors.add("inbox.errors", new ActionMessage("inbox.popserver.error", 
				authRecord.getPop3MailServer(), authRecord.getPop3Port(), authRecord.isApop()) );
		addErrors(request, errors);
		return BaseAction.FAILED;
	}

}
