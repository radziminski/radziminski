import React from 'react';
//import './assets/scss/main.scss';
import './assets/css/style.css';
import Home from './views/Home';
import Event from './views/Event';
import Day from './views/Day';
import Footer from './views/Footer';
import axios from 'axios';
import { BrowserRouter as Router, Switch, Route } from 'react-router-dom';

////////////////////////////////////////////
//////// CREATED BY JAN RADZIMINSKI ////////
////////////////////////////////////////////

// AXIOS CONFIG
axios.defaults.headers.post['Content-Type'] = 'application/x-www-form-urlencoded';
axios.defaults.baseURL = 'http://localhost:3000/';

// App Render
const App = () => {
    return (
        <Router>
            <div className="App">
                <Switch>
                    <Route path="/day/:date" component={Day} />
                    <Route path="/event/:date/:id?" component={Event} />
                    <Route path="/home/:date?" component={Home} />
                    <Route path="/" component={Home} />
                </Switch>
                <Footer />
            </div>
        </Router>
    );
};

export default App;
