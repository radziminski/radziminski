import React from 'react';
import Button from './Button';

const EventCard = ({ id, date, description, onDelete }) => {
    return (
        <div className="event-card">
            <div className="event-card__time">{date.toTimeString().slice(0, 5)}</div>
            <div className="event-card__description">{description}</div>
            <div className="event-card__btns">
                <Button>Edit</Button>
                <Button classTypes={['red']} onClick={() => onDelete(id)}>
                    Delete
                </Button>
            </div>
        </div>
    );
};

export default EventCard;
