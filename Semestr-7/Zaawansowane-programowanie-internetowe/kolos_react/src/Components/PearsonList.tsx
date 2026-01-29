import { Link } from "react-router-dom";
import type { Contact } from "../Model/Contact";

type Props = {
  contacts: Contact[];
};

const PearsonList = ({ contacts }: Props) => {
  return (
    <div>
      <h2>Lista kontaktów</h2>
      <ul>
        {contacts.map((contact) => (
          <li key={contact.id}>
            <Link to={`/person/${contact.id}`}>
              {contact.firstName} {contact.lastName}
            </Link>
          </li>
        ))}
      </ul>
    </div>
  );
};

export default PearsonList;
