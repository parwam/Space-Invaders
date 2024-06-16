﻿#include "../Header/ServiceLocator.h"

// Constructor: Initializes the graphic_service pointer to null and creates services.
ServiceLocator::ServiceLocator()
{
    // Initialize service to null
    graphic_service = nullptr;  
    event_service = nullptr;
    
    createServices();   // Call createServices to instantiate services
}

// Destructor: Cleans up resources by clearing all services
ServiceLocator::~ServiceLocator()
{
    clearAllServices();     // Call clearAllServices to delete any allocated services	
}

void ServiceLocator::createServices()
{
    // Dynamically create a service instance
    graphic_service = new GraphicService(); 
    event_service = new EventService();
}

void ServiceLocator::clearAllServices()
{
    // Delete the service instance
    delete(graphic_service);
    delete(event_service);
    
    // Reset pointer to null to avoid dangling pointer
    graphic_service = nullptr;
    event_service = nullptr;
}

ServiceLocator* ServiceLocator::getInstance()
{
    static ServiceLocator instance;
    return &instance;
}

void ServiceLocator::initialize()
{
    graphic_service->initialize();
    event_service->initialize();
}

void ServiceLocator::update()
{
    // Updates all services
    graphic_service->update();
    event_service->update();
}

void ServiceLocator::render()
{
    // Renders using the services
    graphic_service->render();
}

// Returns a pointer to the currently set graphic service
GraphicService* ServiceLocator::getGraphicService() const { return graphic_service; }
EventService* ServiceLocator::getEventService() const { return event_service; }