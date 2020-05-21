import React, { Component } from 'react';
import './assets/scss/main.scss';
import './App.css';
import Home from './views/Home';

class App extends Component {
    componentDidMount() {
        const xhttp = new XMLHttpRequest();
        xhttp.open('POST', 'http://localhost:3000/event/add', true);
        xhttp.setRequestHeader('Content-type', 'application/json');
        xhttp.setRequestHeader('Access-Control-Allow-Origin', 'origin');

        xhttp.send({
            year: 2020,
            month: 12,
            day: 12,
            hours: 12,
            minutes: 12,
            description: 'aaaaa',
        });
    }

    render() {
        return (
            <div className="App">
                <Home />
            </div>
        );
    }
}

export default App;
