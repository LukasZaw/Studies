import { Link, useParams } from "react-router-dom";
import type { Contact } from "../Model/Contact";

type RouteParams = {
  id: string;
};

type Props = {
  contacts: Contact[];
};

const PearsonDetails = ({ contacts }: Props) => {
  const { id } = useParams<RouteParams>();
  const personId = Number(id);
  const contact = contacts.find((c) => c.id === personId);

  if (!contact) {
    return (
      <div>
        <p>Osoba nie została znaleziona.</p>
        <Link to="/">Wróć do listy</Link>
      </div>
    );
  }

  return (
    <div>
      <h2>Szczegóły kontaktu</h2>
      <p>
        <strong>Imię i nazwisko:</strong> {contact.firstName} {contact.lastName}
      </p>
      <p>
        <strong>Wiek:</strong> {contact.age}
      </p>
      <p>
        <strong>Płeć:</strong> {contact.sex === 0 ? "Mężczyzna" : "Kobieta"}
      </p>
      <p>
        <strong>Adresy e-mail:</strong>
      </p>
      <ul>
        {contact.emails.map((email, index) => (
          <li key={index}>
            {email.value} ({email.category.name})
          </li>
        ))}
      </ul>
      <Link to="/">Wróć </Link> | <Link to={`/edit/${contact.id}`}>Edytuj</Link>
    </div>
  );
};

export default PearsonDetails;
