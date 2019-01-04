package com.ja.jwmail.servlets;

import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionMessage;

import com.ja.jwmail.common.MailMessage;
import com.ja.jwmail.formbeans.AuthenticationRecord;
import com.ja.jwmail.formbeans.BaseFormBean;
import com.ja.jwmail.formbeans.DeleteList;
import com.ja.jwmail.services.POP3Service;

/**
 * 
 * @author Joseph Acosta
 *
 */
public class DeleteMessageAction extends BaseAction {

	@Override
	public String processRequest(BaseFormBean form, HttpServletRequest request,
			HttpServletResponse response, HttpSession session) throws Exception {
		
		ActionErrors errors = new ActionErrors();
		
		// get the pop3 service from the session
		POP3Service pop3Service = new POP3Service();

		// get the auth record from session
		AuthenticationRecord authRecord = (AuthenticationRecord)session.getAttribute(BaseAction.AUTH_RECORD);

                // get the form 
                DeleteList dlist = (DeleteList)form; 
		
		// if we have an authentication record and a pop3 service object
		// we can connect
		if ( pop3Service != null && authRecord != null 
                    && dlist.getAllMessages() != null && dlist.getAllMessages().size() > 0 )
                { 
			boolean connected = pop3Service.connect(authRecord.getUsername(), 
					authRecord.getPassword(), authRecord.getPop3MailServer(), 
					authRecord.getPop3Port(), authRecord.isApop());
			
						// if we are connected 
			if ( connected ) {
				
				// try to delete the messages
				List<String> messages = dlist.getAllMessages();
				
				for ( int i = 0; i < messages.size(); i +=1 ) {
					String msg = messages.get(i);
					if ( msg != null && msg.equals("on") ) {
						pop3Service.deleteMessage(i);
					}				
				} 
			
				// close connection
				pop3Service.disconnect();
				
				return BaseAction.SUCCESS;
			}
		}		
		errors.add("delete.error", new ActionMessage("delete.message.error"));	
		addErrors(request, errors);
		return BaseAction.FAILED;
	}

}
