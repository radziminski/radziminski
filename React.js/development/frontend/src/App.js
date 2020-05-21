import React, { useState } from 'react';
import './assets/scss/main.scss';
import Home from './views/Home';
import Event from './views/Event';
import Day from './views/Day';
import Footer from './views/Footer';

const App = () => {
    const [currView, setCurrView] = useState('home');
    const [currDate, setCurrDate] = useState(new Date());

    const toggleView = (viewName, date) => {
        setCurrView(viewName);
        setCurrDate(date);
    };

    let renderView;
    switch (currView) {
        case 'home':
            renderView = <Home switchView={toggleView} currDate={currDate} />;
            break;
        case 'day':
            renderView = <Day switchView={toggleView} currDate={currDate} />;
            break;
        case 'event':
            renderView = <Event switchView={toggleView} currDate={currDate} />;
            break;
        default:
            renderView = <Home switchView={toggleView} currDate={currDate} />;
            break;
    }
    return (
        <div className="App">
            {renderView}
            <Footer />
        </div>
    );
};

export default App;
