import React from 'react';
import Button from './Button';

const EventCard = ({ id, date, description, onDelete, onEdit }) => {
    const descriptionRender =
        description.length > 15 ? description.slice(0, 14) + '...' : description;
    return (
        <div className="event-card">
            <div className="event-card__time">{date.toTimeString().slice(0, 5)}</div>
            <div className="event-card__description">{descriptionRender}</div>
            <div className="event-card__btns">
                <Button onClick={onEdit}>Edit</Button>
                <Button classTypes={['red']} onClick={() => onDelete(id)}>
                    Delete
                </Button>
            </div>
        </div>
    );
};

export default EventCard;
