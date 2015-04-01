package mail;

import java.util.*;
import javax.mail.*;
import javax.mail.internet.*;

/**
 * Classe pour envoyer un mail vial l'université paris 13
 *
 * @author Jones Magloire
 */
public class SendMail {

	/**
	 * @param mail    a qui on va envoyer msg
	 * @param subject du message
	 * @param msg     contenue
	 *
	 * @throws MessagingException
	 */
	public static void send(String mail, String subject, String msg) throws MessagingException {
		Properties props = System.getProperties();
		props.put("mail.transport.protocol", "smtp");
		props.put("mail.smtp.host", "upn.univ-paris13.fr");
		// ou -Dmail.transport.protocol=smtp ...
		Session session = Session.getInstance(props);
		MimeMessage message = new MimeMessage(session);
		message.setFrom(new InternetAddress("m2pls@univ-paris13.fr"));
		message.setRecipient(Message.RecipientType.TO,
				// ou CC ou BCC
				new InternetAddress(mail));
		message.setSubject(subject);
		message.setText(msg);
		throw new MessagingException("Il faut décommenter Transport.send dans mail.SendMail.send() et être à la fac");
		//Transport.send(message);
	}
}
