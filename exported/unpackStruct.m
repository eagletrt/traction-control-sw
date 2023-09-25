function table = unpackStruct(structure)
    fn = fieldnames(structure);
 
    for i = 1:numel(fn)
        fni = string(fn(i));
        field = structure.(fni);
        busdata(:,i) = field.data;
    end
    table = array2table(busdata, 'VariableNames', fn);
end