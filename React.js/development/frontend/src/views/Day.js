import React, { useState } from 'react';
import { dateToString } from '../utils';
import EventCard from '../components/EventCard';
import Button from '../components/Button';

const Day = (props) => {
    const [events, setEvents] = useState([
        {
            date: new Date(),
            description: 'lalalala',
        },
        {
            date: new Date(),
            description: 'lelelele',
        },
        {
            date: new Date(),
            description: 'lilililil',
        },
    ]);

    const { switchView, currDate } = props;
    const renderedEvents = events.map((el, i) => (
        <EventCard key={i} date={el.date} description={el.description} />
    ));
    return (
        <section className="day-view">
            <h1 className="section-title">Events on {dateToString(currDate)}</h1>
            <div className="day-view__events-box">{renderedEvents}</div>
            <div className="day-view__btns">
                <Button onClick={() => switchView('event', currDate)}>Add New</Button>
                <Button classTypes={['red']} onClick={() => switchView('home', currDate)}>
                    Back
                </Button>
            </div>
        </section>
    );
};

export default Day;
