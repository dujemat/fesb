import React from 'react';
import './Header.css';

function Header() {
  return (
    <div className="header">
      <ul className="menu">
        <li className="menu-item">
          <a href="#">Države na A</a>
          <ul className="sub-menu">
            <li><a href="#">Albanija</a></li>
            <li><a href="#">Azerbajdžan</a></li>
            <li><a href="#">Afganistan</a></li>
          </ul>
        </li>
        <li className="menu-item">
          <a href="#">Države na B</a>
          <ul className="sub-menu">
            <li><a href="#">Bugarska</a></li>
            <li><a href="#">BiH</a></li>
            <li><a href="#">Belgija</a></li>
          </ul>
        </li>
        <li className="menu-item">
          <a href="#">Države na S</a>
          <ul className="sub-menu">
            <li><a href="#">Srbija</a></li>
            <li><a href="#">Slovačka</a></li>
            <li><a href="#">Slovenija</a></li>
          </ul>
        </li>
      </ul>
    </div>
  );
}

export default Header;
