const express = require('express');
const session = require('express-session');
const path = require('path');
const app = express();

app.use(express.urlencoded({ extended: true }));

app.use(session({
  secret: 'tajny_klucz',
  resave: false,
  saveUninitialized: true,
  cookie: {
    maxAge: 10000 // 10 sekund w milisekundach
  }
}));

app.use(express.static(path.join(__dirname, 'public')));

const LOGIN = 'admin';
const PASSWORD = '1234';

app.get('/', (req, res) => {
  if (req.session.zalogowany) {
    res.sendFile(path.join(__dirname, 'ukryty.html'));
  } else {
    res.sendFile(path.join(__dirname, 'index.html'));
  }
});

app.post('/login', (req, res) => {
  const { username, password } = req.body;
  if (username === LOGIN && password === PASSWORD) {
    req.session.zalogowany = true;
    res.redirect('/');
  } else {
    res.send('Błędny login lub hasło. <a href="/">Spróbuj ponownie</a>.');
  }
});

app.get('/logout', (req, res) => {
  req.session.destroy(err => {
    res.redirect('/');
  });
});

app.listen(5000, () => {
  console.log('Aplikacja działa na http://localhost:5000');
});
