import React from 'react';
import Calendar from '../components/Calendar';

const Home = ({ switchView, currDate }) => {
    return (
        <section className="home-view">
            <Calendar currDate={currDate} switchView={switchView} />
        </section>
    );
};

export default Home;
